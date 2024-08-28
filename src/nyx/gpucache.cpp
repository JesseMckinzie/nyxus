#ifdef USE_GPU

#include <unordered_map>
#include "gpucache.h"
#include "gpu/geomoments.cuh"
#include "roi_cache.h"


// functions implemented in gpucache.cu :
namespace NyxusGpu
{
	bool gpu_delete(void* devptr);
	bool allocate_on_device(void** ptr, size_t szb);
	bool upload_on_device (void* devbuffer, void* hobuffer, size_t szb);
	bool download_on_host(void* hobuffer, void* devbuffer, size_t szb);
	bool devicereduce_evaluate_buffer_szb(size_t& devicereduce_buf_szb, size_t maxLen);
}

#define OK(x) if (x == false) \
{ \
	std::cerr << "gpu cache related error in " << __FILE__ << ":" << __LINE__; \
	return false; \
} \

#define OKV(x) if (x == false) \
{ \
	std::cerr << "gpu cache related error in " << __FILE__ << ":" << __LINE__; \
	return; \
} \

template<>
bool GpuCache<Pixel2>::clear()
{
	if (hobuffer)
	{
		std::free(hobuffer); // delete hobuffer;
		hobuffer = nullptr;

		// device side buffer
		if (!NyxusGpu::gpu_delete(devbuffer))
			return false;
		devbuffer = nullptr;
	}

	if (ho_lengths)
	{
		std::free(ho_lengths); // delete ho_lengths;
		ho_lengths = nullptr;
	}

	if (ho_offsets)
	{
		std::free(ho_offsets); // delete ho_offsets;
		ho_offsets = nullptr;

		// device side buffer
		if (!NyxusGpu::gpu_delete(dev_offsets))
			return false;
		dev_offsets = nullptr;
	}

	return true;
}

template<>
bool GpuCache<gpureal>::clear()
{
	if (hobuffer)
	{
		std::free(hobuffer); // delete hobuffer;
		hobuffer = nullptr;

		// device side buffer
		if (!NyxusGpu::gpu_delete(devbuffer))
			return false;
		devbuffer = nullptr;
	}

	if (ho_lengths)
	{
		std::free(ho_lengths); // delete ho_lengths;
		ho_lengths = nullptr;
	}

	if (ho_offsets)
	{
		std::free(ho_offsets); // delete ho_offsets;
		ho_offsets = nullptr;

		// device side buffer
		if (!NyxusGpu::gpu_delete(dev_offsets))
			return false;
		dev_offsets = nullptr;
	}

	return true;
}

template<>
bool GpuCache<size_t>::clear()
{
	throw std::runtime_error("unimplemented GpuCache/numeric/clear");
	return true;
}

template<>
bool GpuCache<Pixel2>::alloc (size_t total_len__, size_t num_rois__)
{
	total_len = total_len__;
	num_rois = num_rois__;

	// allocate on device
	std::cout << "allocate on device ... \n";
	size_t szb = total_len * sizeof(devbuffer[0]);
	std::cout << "allocating on device [" << total_len << "] " << szb << "\n";
	if (!NyxusGpu::allocate_on_device ((void**)&devbuffer, szb))
		return false;

	szb = num_rois * sizeof(dev_offsets[0]);
	if (!NyxusGpu::allocate_on_device ((void**)&dev_offsets, szb))
		return false;

	// allocate on host	
	std::cout << "hobuffer := new Pixel2 " << total_len << "=" << sizeof(Pixel2)*total_len << "\n";
	
	hobuffer = (Pixel2*) std::malloc(total_len * sizeof(hobuffer[0])); 
	if (!hobuffer) return false;
	
	std::cout << "ho_lengths := new size_t " << num_rois << "\n";
	ho_lengths = (size_t*) std::malloc(num_rois * sizeof(ho_lengths[0])); 
	if (!ho_lengths) return false;

	std::cout << "ho_offsets := new size_t " << num_rois << "\n";
	ho_offsets = (size_t*) std::malloc(num_rois * sizeof(ho_offsets[0])); 
	
	return true;
}

template<>
size_t GpuCache<Pixel2>::szb(size_t total_len, size_t num_rois)
{
	// see implementation of alloc() !
	size_t s1 = total_len * sizeof(devbuffer[0]);
	size_t s2 = num_rois * sizeof(dev_offsets[0]);
	return s1 + s2;
}

template<>
bool GpuCache<gpureal>::alloc(size_t roi_buf_len, size_t num_rois__)
{
	num_rois = num_rois__;
	total_len = roi_buf_len * num_rois;

	// allocate on host	
	hobuffer = (gpureal*) std::malloc(total_len * sizeof(hobuffer[0])); 

	//		not allocating ho_lengths
	//		not allocating ho_offsets

	// allocate on device
	size_t szb = total_len * sizeof(devbuffer[0]);
	if (!NyxusGpu::allocate_on_device((void**)&devbuffer, szb))
		return false;

	//		not allocating dev_offsets

	return true;
}

template<>
size_t GpuCache<gpureal>::szb(size_t total_len, size_t num_rois)
{
	size_t szb = total_len * sizeof(devbuffer[0]);
	return szb;
}

template<>
bool GpuCache<Pixel2>::upload()
{
	size_t szb = total_len * sizeof(devbuffer[0]);
	if (!NyxusGpu::upload_on_device((void*)devbuffer, (void*)hobuffer, szb))
		return false;

	szb = num_rois * sizeof(dev_offsets[0]);
	if (!NyxusGpu::upload_on_device((void*)dev_offsets, (void*)ho_offsets, szb))
		return false;

	return true;
}

template<>
bool GpuCache<gpureal>::download()
{
	size_t szb = total_len * sizeof(devbuffer[0]);
	if (!NyxusGpu::download_on_host ((void*)hobuffer, (void*)devbuffer, szb))
		return false;

	return true;
}

template<>
bool GpuCache<cufftDoubleComplex>::clear()
{
	if (hobuffer)
	{
		std::free(hobuffer); 
		hobuffer = nullptr;

		// device side buffer
		if (!NyxusGpu::gpu_delete(devbuffer))
			return false;
		devbuffer = nullptr;
	}

	if (ho_lengths)
	{
		std::free(ho_lengths); 
		ho_lengths = nullptr;
	}

	if (ho_offsets)
	{
		std::free(ho_offsets); 
		ho_offsets = nullptr;

		// device side buffer
		if (!NyxusGpu::gpu_delete(dev_offsets))
			return false;
		dev_offsets = nullptr;
	}

	return true;
}

template<>
bool GpuCache<cufftDoubleComplex>::alloc(size_t roi_buf_len, size_t num_rois__)
{
	num_rois = num_rois__;
	total_len = roi_buf_len * num_rois;

	// allocate on host	
	hobuffer = (cufftDoubleComplex*)std::malloc(total_len * sizeof(hobuffer[0])); 

	//		not allocating ho_lengths
	//		not allocating ho_offsets

	// allocate on device
	size_t szb = total_len * sizeof(devbuffer[0]);
	if (!NyxusGpu::allocate_on_device((void**)&devbuffer, szb))
		return false;

	//		not allocating dev_offsets

	return true;
}

template<>
bool GpuCache<cufftDoubleComplex>::download()
{
	size_t szb = total_len * sizeof(devbuffer[0]);
	if (!NyxusGpu::download_on_host((void*)hobuffer, (void*)devbuffer, szb))
		return false;

	return true;
}

template<>
bool GpuCache<PixIntens>::clear()
{
	if (hobuffer)
	{
		std::free(hobuffer); 
		hobuffer = nullptr;

		// device side buffer
		if (!NyxusGpu::gpu_delete(devbuffer))
			return false;
		devbuffer = nullptr;
	}

	if (ho_lengths)
	{
		std::free(ho_lengths); 
		ho_lengths = nullptr;
	}

	if (ho_offsets)
	{
		std::free(ho_offsets); 
		ho_offsets = nullptr;

		// device side buffer
		if (!NyxusGpu::gpu_delete(dev_offsets))
			return false;
		dev_offsets = nullptr;
	}

	return true;
}

template<>
bool GpuCache<PixIntens>::alloc(size_t roi_buf_len, size_t num_rois__)
{
	num_rois = num_rois__;
	total_len = roi_buf_len * num_rois;

	// allocate on host	
	hobuffer = (PixIntens*) std::malloc(total_len * sizeof(hobuffer[0])); 

	//		not allocating ho_lengths
	//		not allocating ho_offsets

	// allocate on device
	size_t szb = total_len * sizeof(devbuffer[0]);
	if (!NyxusGpu::allocate_on_device((void**)&devbuffer, szb))
		return false;

	return true;
}

//********* float

template<>
bool GpuCache<float>::clear()
{
	if (hobuffer)
	{
		std::free(hobuffer);
		hobuffer = nullptr;

		// device side buffer
		if (!NyxusGpu::gpu_delete(devbuffer))
			return false;
		devbuffer = nullptr;
	}

	if (ho_lengths)
	{
		std::free(ho_lengths); 
		ho_lengths = nullptr;
	}

	if (ho_offsets)
	{
		std::free(ho_offsets); 
		ho_offsets = nullptr;

		// device side buffer
		if (!NyxusGpu::gpu_delete(dev_offsets))
			return false;
		dev_offsets = nullptr;
	}

	return true;
}

template<>
bool GpuCache<float>::alloc(size_t roi_buf_len, size_t num_rois__)
{
	num_rois = num_rois__;
	total_len = roi_buf_len * num_rois;

	// allocate on host	
	hobuffer = (float*)std::malloc(total_len * sizeof(hobuffer[0])); 

	//		not allocating ho_lengths 
	//		not allocating ho_offsets 

	// allocate on device
	size_t szb = total_len * sizeof(devbuffer[0]);
	if (!NyxusGpu::allocate_on_device((void**)&devbuffer, szb))
		return false;

	return true;
}

template<>
bool GpuCache<float>::download()
{
	size_t szb = total_len * sizeof(devbuffer[0]);
	if (!NyxusGpu::download_on_host((void*)hobuffer, (void*)devbuffer, szb))
		return false;

	return true;
}

namespace NyxusGpu
{
	size_t ram_comsumption_szb(
		size_t roi_cloud_len,
		size_t roi_kontur_cloud_len,
		size_t n_rois, 
		size_t roi_w,
		size_t roi_h,
		int n_gabor_filters,
		int gabor_ker_side)
	{
		size_t szb_clo = GpuCache<Pixel2>::/*clouds.*/szb(roi_cloud_len, n_rois),
			szb_kon = GpuCache<Pixel2>::/*konturs.*/szb(roi_kontur_cloud_len, n_rois),
			szb_mom_ri = sizeof(RealPixIntens) * roi_cloud_len,
			szb_moms_pr = sizeof(double) * roi_cloud_len * 16,
			szb_state = GpuCache<gpureal>::/*state.*/szb(GpusideState::__COUNT__, n_rois),
			szb_moms_dr = sizeof(void*/*devicereduce_buf[0]*/) * roi_cloud_len,	// always enough
			szb_imat = 2 * sizeof(StatsInt) * roi_w * roi_h,		// erosion requires 2 matrices
			szb_gabor1 = 3 * sizeof(cufftDoubleComplex) * n_gabor_filters * (roi_w + gabor_ker_side - 1) * (roi_h + gabor_ker_side - 1),	// 3 arrays
			szb_gabor2 = sizeof(PixIntens) * n_gabor_filters * (roi_w + gabor_ker_side - 1) * (roi_h + gabor_ker_side - 1);

		size_t szb = szb_clo +
			szb_kon +
			szb_mom_ri +
			szb_moms_pr +
			szb_state +
			szb_moms_dr +
			szb_imat + 
			szb_gabor1 + 
			szb_gabor2;

		return szb;
	}

	bool allocate_gpu_cache(
		// out
		GpuCache<Pixel2>& clouds,	// geo moments
		GpuCache<Pixel2>& konturs,
		RealPixIntens** realintens,
		double** prereduce,
		GpuCache<gpureal>& intermediate,
		size_t& devicereduce_buf_szb,
		void** devicereduce_buf,
		size_t & batch_len,
		PixIntens** imat1,				// erosion
		PixIntens** imat2,				// 
		GpuCache <cufftDoubleComplex>& gabor_linear_image,	// gabor
		GpuCache <cufftDoubleComplex>& gabor_result,
		GpuCache <cufftDoubleComplex>& gabor_linear_kernel,
		GpuCache <PixIntens> & gabor_energy_image,
		// in
		size_t roi_cloud_len,				// ideal
		size_t roi_kontur_cloud_len,	// ideal
		size_t n_rois,
		size_t roi_area,
		size_t roi_w,
		size_t roi_h,
		int n_gabor_filters,
		int gabor_ker_side)
	{
		//****** plan GPU memory
		size_t amt = 0; 
		OK(gpu_get_free_mem(amt));

		std::cout << "GPU mem amt = " << amt << "\n";

		int n_gabFilters = n_gabor_filters + 1;		// '+1': an extra filter for the baseline signal

		// Calculate the amt of required memory
		size_t ccl0 = roi_area * n_rois;	// combined cloud length, initial
		size_t szb = ram_comsumption_szb (ccl0, ccl0, n_rois, roi_w, roi_h, n_gabFilters, gabor_ker_side);

		std::cout << "szb (ideal:" << roi_cloud_len << ", ideal:" << roi_kontur_cloud_len << ", " << n_rois << ") = " << szb << "\n";

		batch_len = n_rois;
		size_t critAmt = amt / 4;	// critical RAM

		std::cout << "critAmt = " << critAmt << "\n";

		if (critAmt <= szb)
		{
			size_t try_nrois = 0;
			for (try_nrois = n_rois; try_nrois>=1; try_nrois--)
			{
				size_t ccl = roi_area * try_nrois;	// combined cloud length
				size_t try_szb = ram_comsumption_szb (ccl, ccl, try_nrois, roi_w, roi_h, n_gabFilters, gabor_ker_side);

				if (try_nrois % 10 == 0)
					std::cout << "try_szb (" << ccl << ", " << ccl << ", " << try_nrois << ") = " << try_szb << "\n";

				if (critAmt > try_szb)
				{
					std::cout << "good! batch_len=" << try_nrois << "\n";
					batch_len = try_nrois;
					break;
				}
			}

			// have we found a compromise ?
			if (batch_len == n_rois)
			{
				std::cerr << "error: a compromise GPU batch_length was not found \n";
				return false;
			}
		}

		size_t batch_roi_cloud_len = roi_area * batch_len;

		std::cout << "batch_len = " << batch_len << " of ideal " << n_rois << "\n";
		std::cout << "batch_roi_cloud_len = " << batch_roi_cloud_len  << "\n";

		//****** allocate

		// ROI clouds
		OK(clouds.clear());
		OK(clouds.alloc(batch_roi_cloud_len, batch_len));

		// contours
		OK(konturs.clear());
		OK(konturs.alloc(batch_roi_cloud_len, batch_len));

		// moments / real intensities
		OK(NyxusGpu::allocate_on_device((void**)realintens, sizeof(RealPixIntens) * batch_roi_cloud_len));

		// moments / pre-reduce
		OK(NyxusGpu::allocate_on_device((void**)prereduce, sizeof(double) * batch_roi_cloud_len * 16));	// 16 is the max number of simultaneous totals calculated by a kernel, e.g. RM00-33

		// moments / intermediate
		OK(intermediate.alloc(GpusideState::__COUNT__, batch_len));

		// moments / CUB DeviceReduce's temp buffer
		OK(NyxusGpu::devicereduce_evaluate_buffer_szb(devicereduce_buf_szb, batch_roi_cloud_len));
		OK(NyxusGpu::allocate_on_device((void**)devicereduce_buf, devicereduce_buf_szb));

		// erosion / image matrices 1 and 2
		OK(NyxusGpu::allocate_on_device((void**)imat1, sizeof(imat1[0]) * roi_w * roi_h));
		OK(NyxusGpu::allocate_on_device((void**)imat2, sizeof(imat2[0]) * roi_w * roi_h));

		// Gabor
		size_t gabTotlen = (roi_w + gabor_ker_side -1) * (roi_h + gabor_ker_side -1) * n_gabFilters;
		OK (gabor_linear_image.alloc(gabTotlen, 1));
		OK (gabor_result.alloc(gabTotlen, 1));
		OK (gabor_linear_kernel.alloc(gabTotlen, 1));
		OK (gabor_energy_image.alloc(gabTotlen, 1));

		return true;
	}

	void send_roi_batch_data_2_gpu (
		// out
		GpuCache<Pixel2> & clouds,
		GpuCache<Pixel2> & konturs,
		RealPixIntens ** realintens,
		double ** prereduce,
		GpuCache<gpureal>& intermediate,
		size_t & devicereduce_buf_szb,
		void** devicereduce_buf,
		// in
		const std::vector<int>& labels, 
		std::unordered_map <int, LR>& roi_data,
		size_t batch_offset, 
		size_t batch_len)
	{
		//***** ROI clouds
		
		// stats of ROI cloud sizes
		size_t totCloLen = 0, maxLen = 0;
		for (size_t i=batch_offset; i<batch_len; i++)
		{
			int lbl = labels[i];
			LR& roi = roi_data[lbl];
			auto n = roi.raw_pixels.size();
			totCloLen += n;
			maxLen = (std::max)(maxLen, n);
		}

		//****** contours

		// stats of ROI cloud sizes
		size_t totKontLen = 0;
		for (size_t i = batch_offset; i < batch_len; i++)
		{
			int lbl = labels[i];
			LR& roi = roi_data[lbl];
			totKontLen += roi.contour.size();
		}

		//****** clouds as a solid buffer
		size_t off = 0;
		size_t roiIdx = 0;
		for (size_t i = batch_offset; i < batch_len; i++)
		{
			int lbl = labels[i];
			LR& roi = roi_data[lbl];

			clouds.ho_lengths[roiIdx] = roi.raw_pixels.size();
			clouds.ho_offsets[roiIdx] = off;
			roiIdx++;

			// save to buffer fixingb pixel coordinates
			auto xmin = roi.aabb.get_xmin();
			auto ymin = roi.aabb.get_ymin();
			for (Pixel2 p : roi.raw_pixels)	// copy, not reference
			{
				p.x -= xmin;
				p.y -= ymin;
				clouds.hobuffer[off++] = p;
			}
		}

		//****** contours as a solid buffer

		off = 0;
		roiIdx = 0;
		for (size_t i = batch_offset; i < batch_len; i++)
		{
			int lbl = labels[i];
			LR& roi = roi_data[lbl];

			konturs.ho_lengths[roiIdx] = roi.contour.size();
			konturs.ho_offsets[roiIdx] = off;
			roiIdx++;

			// save to buffer fixing pixel coordinates
			auto xmin = roi.aabb.get_xmin();
			auto ymin = roi.aabb.get_ymin();
			for (Pixel2 p : roi.contour)	// copy, not reference
			{
				p.x -= xmin;
				p.y -= ymin;
				konturs.hobuffer[off++] = p;
			}
		}

		//****** upload

		OKV(clouds.upload());
		OKV(konturs.upload());
	}

	bool free_gpu_cache (
		GpuCache<Pixel2>& clouds,
		GpuCache<Pixel2>& konturs,
		RealPixIntens* & realintens,
		double* & prereduce,
		GpuCache<gpureal> & intermediate,
		void* & tempstorage,
		PixIntens* imat1,
		PixIntens* imat2,
		GpuCache <cufftDoubleComplex>& gabor_linear_image,
		GpuCache <cufftDoubleComplex>& gabor_result,
		GpuCache <cufftDoubleComplex>& gabor_linear_kernel,
		GpuCache <PixIntens>& gabor_energy_image)
	{
		// moments

		OK(clouds.clear());
		OK(konturs.clear());
		OK (NyxusGpu::gpu_delete (realintens));
		OK (NyxusGpu::gpu_delete (prereduce));
		OK (intermediate.clear());
		OK (NyxusGpu::gpu_delete (tempstorage));
		realintens = nullptr;
		prereduce = nullptr;
		OK(intermediate.clear());
		tempstorage = nullptr;	// devicereduce's temp storage

		// erosion

		OK(NyxusGpu::gpu_delete (imat1));
		OK(NyxusGpu::gpu_delete (imat2));

		// Gabor

		OK (gabor_linear_image.clear());
		OK (gabor_result.clear());
		OK (gabor_linear_kernel.clear());
		OK (gabor_energy_image.clear());

		return true;
	}

#ifdef USE_GPU

	void send_roi_data_gpuside(const std::vector<int>& roilabels, std::unordered_map <int, LR>& roidata, size_t batch_offset, size_t batch_len)
	{
		NyxusGpu::send_roi_batch_data_2_gpu(
			// out
			NyxusGpu::gpu_roiclouds_2d,
			NyxusGpu::gpu_roicontours_2d,
			&NyxusGpu::dev_realintens,
			&NyxusGpu::dev_prereduce,
			NyxusGpu::gpu_featurestatebuf,
			NyxusGpu::devicereduce_temp_storage_szb,
			&NyxusGpu::dev_devicereduce_temp_storage,	
			// in
			roilabels,
			roidata,
			batch_offset,
			batch_len);
	}

	void free_roi_data_gpuside()
	{
		if (!NyxusGpu::free_gpu_cache(
			NyxusGpu::gpu_roiclouds_2d,
			NyxusGpu::gpu_roicontours_2d,
			NyxusGpu::dev_realintens,
			NyxusGpu::dev_prereduce,
			NyxusGpu::gpu_featurestatebuf,
			NyxusGpu::dev_devicereduce_temp_storage,
			NyxusGpu::dev_imat1,
			NyxusGpu::dev_imat2,
			NyxusGpu::gabor_linear_image,
			NyxusGpu::gabor_result,
			NyxusGpu::gabor_linear_kernel,
			NyxusGpu::gabor_energy_image))
		{
			std::cerr << "error in NyxusGpu::free_gpu_cache() " << __FILE__ << "\n";
		}
	}

	// GPU cache of ROI batch data
	GpuCache<Pixel2> gpu_roiclouds_2d;
	GpuCache<Pixel2> gpu_roicontours_2d;
	//--later-- GpuCache<size_t> gpu_roicontours_2d;
	RealPixIntens* dev_realintens = nullptr;			// max cloud size over batch
	double* dev_prereduce = nullptr;						// --"--
	GpuCache<gpureal> gpu_featurestatebuf;					// n_rois * GeomomentsState::__COUNT__	

	void* dev_devicereduce_temp_storage = nullptr;    // allocated [] elements by cub::DeviceReduce::Sum()
	size_t devicereduce_temp_storage_szb;
	size_t gpu_batch_len = 0;

	// erosion

	PixIntens* dev_imat1;
	PixIntens* dev_imat2;

	// Gabor

	GpuCache <cufftDoubleComplex> gabor_linear_image;
	GpuCache <cufftDoubleComplex> gabor_result;
	GpuCache <cufftDoubleComplex> gabor_linear_kernel;
	GpuCache <PixIntens> gabor_energy_image;

#endif

} // NyxusGpu

#endif
