#pragma once

struct NyxusPixel 
{
	size_t x, y;
	unsigned int intensity;
};

//
//==== Phantom for testing pixel intensity features
//

const static NyxusPixel pixelIntensityFeaturesTestData[] = {
	{8, 0, 11079}, 	{9, 0, 13771}, 	{10, 0, 17664}, 	{11, 0, 19552}, 	{7, 1, 12955},
	{8, 1, 16999}, 	{9, 1, 23426}, 	{10, 1, 27615}, 	{11, 1, 24075},
	{6, 2, 13377}, 	{7, 2, 16329}, 	{8, 2, 23426}, 	{9, 2, 32845},
	{10, 2, 32508}, 	{11, 2, 25078}, 	{12, 2, 18919}, 	{6, 3, 17997},
	{7, 3, 23791}, 	{8, 3, 33450}, 	{9, 3, 37964}, 	{10, 3, 30608},
	{11, 3, 24692}, 	{12, 3, 17311}, 	{5, 4, 16666}, 	{6, 4, 24692},
	{7, 4, 35309}, 	{8, 4, 42426}, 	{9, 4, 39730}, 	{10, 4, 31858},
	{11, 4, 23791}, 	{12, 4, 16329}, 	{4, 5, 14563}, 	{5, 5, 21241},
	{6, 5, 33129}, 	{7, 5, 43413}, 	{8, 5, 46137}, 	{9, 5, 40035},
	{10, 5, 31229}, 	{11, 5, 21866}, 	{12, 5, 15980}, 	{4, 6, 16329},
	{5, 6, 25691}, 	{6, 6, 39730}, 	{7, 6, 47546}, 	{8, 6, 47546},
	{9, 6, 41882}, 	{10, 6, 29962}, 	{11, 6, 19552}, 	{12, 6, 15671},
	{3, 7, 14563}, 	{4, 7, 22191}, 	{5, 7, 33129}, 	{6, 7, 44123},
	{7, 7, 51472}, 	{8, 7, 51805}, 	{9, 7, 40973}, 	{10, 7, 28655},
	{11, 7, 17997}, 	{12, 7, 15338}, 	{2, 8, 12045}, 	{3, 8, 19552},
	{4, 8, 29645}, 	{5, 8, 41261}, 	{6, 8, 47952}, 	{7, 8, 52483},
	{8, 8, 49300}, 	{9, 8, 41561}, 	{10, 8, 24692}, 	{11, 8, 17664},
	{12, 8, 14989}, 	{2, 9, 15980}, 	{3, 9, 26633}, 	{4, 9, 42170},
	{5, 9, 46730}, 	{6, 9, 50790}, 	{7, 9, 49507}, 	{8, 9, 49117},
	{9, 9, 35309}, 	{10, 9, 22191}, 	{11, 9, 17311}, 	{1, 10, 14563},
	{2, 10, 22191}, 	{3, 10, 37660}, 	{4, 10, 50603}, 	{5, 10, 53295},
	{6, 10, 53952}, 	{7, 10, 50067}, 	{8, 10, 45504}, 	{9, 10, 30920},
	{10, 10, 20238}, 	{11, 10, 16329}, 	{1, 11, 18635}, 	{2, 11, 32845},
	{3, 11, 49698}, 	{4, 11, 59194}, 	{5, 11, 59340}, 	{6, 11, 55585},
	{7, 11, 49300}, 	{8, 11, 39730}, 	{9, 11, 25691}, 	{10, 11, 19552},
	{11, 11, 16329}, 	{0, 12, 15338}, 	{1, 12, 25382}, 	{2, 12, 47952},
	{3, 12, 58613}, 	{4, 12, 59490}, 	{5, 12, 62560}, 	{6, 12, 58037},
	{7, 12, 46908}, 	{8, 12, 31550}, 	{9, 12, 20900}, 	{10, 12, 17664},
	{0, 13, 19552}, 	{1, 13, 32191}, 	{2, 13, 53295}, 	{3, 13, 63116},
	{4, 13, 64090}, 	{5, 13, 60615}, 	{6, 13, 50790}, 	{7, 13, 39174},
	{8, 13, 26048}, 	{9, 13, 19552}, 	{10, 13, 16999}, 	{0, 14, 24075},
	{1, 14, 41261}, 	{2, 14, 55585}, 	{3, 14, 63392}, 	{4, 14, 58187},
	{5, 14, 48549}, 	{6, 14, 37116}, 	{7, 14, 27944}, 	{8, 14, 21241},
	{9, 14, 16999}, 	{0, 15, 28655}, 	{1, 15, 44623}, 	{2, 15, 52296},
	{3, 15, 55585}, 	{4, 15, 45723}, 	{5, 15, 31550}, 	{6, 15, 25078},
	{7, 15, 20238}, 	{8, 15, 18282}, 	{1, 16, 35938}, 	{2, 16, 37964},
	{3, 16, 36206}, 	{4, 16, 25078}, 	{5, 16, 20900}, 	{6, 16, 18635},
	{7, 16, 16666}, 	{2, 17, 20563}, 	{3, 17, 17664}, 	{4, 17, 16666},
	{5, 17, 16666}, };

//
//==== IBSI test data converted from https://github.com/theibsi/data_sets/tree/master/ibsi_1_digital_phantom/dicom
//
//
// Conversion code:
// 
//	% -- intensity --
//	inten_info = dicominfo('/path/to/ibsi_1_digital_phantom/image/phantom.dcm');
//	I_dcm = dicomread(inten_info);
//	sz_I = size(I_dcm);
//	for (z = 1 : sz_I(4)) % slice index is size(4)
//		fpath_I = ['/path/to/ibsi_1_digital_phantom_converted/image/phantom' sprintf('_z%d', z) '.tiff'];
//		save2tif(fpath_I, I_dcm(:, : , 1, z));
//
//		% G - test friendly format :
//		lineOfCode = sprintf('const static NyxusPixel ibsi_phantom_z%d_intensity[] = {\n', z);
//		for y = 1:sz_I(2)
//			for x = 1 : sz_I(1)
//				lineOfCode = [lineOfCode sprintf('{/*x*/%d, /*y*/%d, %d}, ', x, y, I_dcm(x, y, 1, z))];
//			end
//			lineOfCode = [lineOfCode '\n'];
//		end
//		lineOfCode = [lineOfCode ' };\n\n'];
//		fprintf(1, lineOfCode);
//	end
//
//	% -- mask --
//	mask_info = dicominfo('/path/to/ibsi_1_digital_phantom/mask/mask.dcm');
//	M_dcm = dicomread(mask_info);
//	sz_M = size(M_dcm);
//	for (z = 1 : sz_M(4)) % slice index is size(4)
//		fpath_M = ['/path/to/ibsi_1_digital_phantom_converted/mask/phantom' sprintf('_z%d', z) '.tiff'];
//		save2tif(fpath_M, M_dcm(:, : , 1, z));
//
//		% G - test friendly format :
//		lineOfCode = sprintf('const static NyxusPixel ibsi_phantom_z%d_mask[] = {\n', z);
//		for y = 1:sz_M(2)
//			for x = 1 : sz_M(1)
//				lineOfCode = [lineOfCode sprintf('{/*x*/%d, /*y*/%d, %d}, ', x, y, M_dcm(x, y, 1, z))];
//			end
//			lineOfCode = [lineOfCode '\n'];
//		end
//		lineOfCode = [lineOfCode ' };\n\n'];
//		fprintf(1, lineOfCode);
//	end
//


const static NyxusPixel ibsi_phantom_z1_intensity[] = {
{/*x*/1, /*y*/1, 4}, {/*x*/2, /*y*/1, 4}, {/*x*/3, /*y*/1, 1}, {/*x*/4, /*y*/1, 1},
{/*x*/1, /*y*/2, 4}, {/*x*/2, /*y*/2, 4}, {/*x*/3, /*y*/2, 1}, {/*x*/4, /*y*/2, 1},
{/*x*/1, /*y*/3, 6}, {/*x*/2, /*y*/3, 6}, {/*x*/3, /*y*/3, 6}, {/*x*/4, /*y*/3, 6},
{/*x*/1, /*y*/4, 4}, {/*x*/2, /*y*/4, 1}, {/*x*/3, /*y*/4, 1}, {/*x*/4, /*y*/4, 1},
{/*x*/1, /*y*/5, 1}, {/*x*/2, /*y*/5, 1}, {/*x*/3, /*y*/5, 1}, {/*x*/4, /*y*/5, 1},
};

const static NyxusPixel ibsi_phantom_z2_intensity[] = {
{/*x*/1, /*y*/1, 4}, {/*x*/2, /*y*/1, 1}, {/*x*/3, /*y*/1, 1}, {/*x*/4, /*y*/1, 1},
{/*x*/1, /*y*/2, 1}, {/*x*/2, /*y*/2, 1}, {/*x*/3, /*y*/2, 1}, {/*x*/4, /*y*/2, 1},
{/*x*/1, /*y*/3, 6}, {/*x*/2, /*y*/3, 3}, {/*x*/3, /*y*/3, 9}, {/*x*/4, /*y*/3, 1},
{/*x*/1, /*y*/4, 4}, {/*x*/2, /*y*/4, 1}, {/*x*/3, /*y*/4, 1}, {/*x*/4, /*y*/4, 1},
{/*x*/1, /*y*/5, 1}, {/*x*/2, /*y*/5, 1}, {/*x*/3, /*y*/5, 1}, {/*x*/4, /*y*/5, 1},
};

const static NyxusPixel ibsi_phantom_z3_intensity[] = {
{/*x*/1, /*y*/1, 1}, {/*x*/2, /*y*/1, 1}, {/*x*/3, /*y*/1, 1}, {/*x*/4, /*y*/1, 1},
{/*x*/1, /*y*/2, 4}, {/*x*/2, /*y*/2, 1}, {/*x*/3, /*y*/2, 1}, {/*x*/4, /*y*/2, 1},
{/*x*/1, /*y*/3, 6}, {/*x*/2, /*y*/3, 6}, {/*x*/3, /*y*/3, 1}, {/*x*/4, /*y*/3, 1},
{/*x*/1, /*y*/4, 1}, {/*x*/2, /*y*/4, 1}, {/*x*/3, /*y*/4, 1}, {/*x*/4, /*y*/4, 1},
{/*x*/1, /*y*/5, 1}, {/*x*/2, /*y*/5, 1}, {/*x*/3, /*y*/5, 1}, {/*x*/4, /*y*/5, 1},
};

const static NyxusPixel ibsi_phantom_z4_intensity[] = {
{/*x*/1, /*y*/1, 1}, {/*x*/2, /*y*/1, 1}, {/*x*/3, /*y*/1, 1}, {/*x*/4, /*y*/1, 1},
{/*x*/1, /*y*/2, 4}, {/*x*/2, /*y*/2, 4}, {/*x*/3, /*y*/2, 4}, {/*x*/4, /*y*/2, 4},
{/*x*/1, /*y*/3, 4}, {/*x*/2, /*y*/3, 4}, {/*x*/3, /*y*/3, 4}, {/*x*/4, /*y*/3, 4},
{/*x*/1, /*y*/4, 1}, {/*x*/2, /*y*/4, 1}, {/*x*/3, /*y*/4, 1}, {/*x*/4, /*y*/4, 1},
{/*x*/1, /*y*/5, 1}, {/*x*/2, /*y*/5, 1}, {/*x*/3, /*y*/5, 1}, {/*x*/4, /*y*/5, 1},
};

const static NyxusPixel ibsi_phantom_z1_mask[] = {
{/*x*/1, /*y*/1, 1}, {/*x*/2, /*y*/1, 1}, {/*x*/3, /*y*/1, 1}, {/*x*/4, /*y*/1, 1},
{/*x*/1, /*y*/2, 1}, {/*x*/2, /*y*/2, 1}, {/*x*/3, /*y*/2, 1}, {/*x*/4, /*y*/2, 1},
{/*x*/1, /*y*/3, 1}, {/*x*/2, /*y*/3, 1}, {/*x*/3, /*y*/3, 1}, {/*x*/4, /*y*/3, 1},
{/*x*/1, /*y*/4, 1}, {/*x*/2, /*y*/4, 1}, {/*x*/3, /*y*/4, 1}, {/*x*/4, /*y*/4, 1},
{/*x*/1, /*y*/5, 1}, {/*x*/2, /*y*/5, 1}, {/*x*/3, /*y*/5, 1}, {/*x*/4, /*y*/5, 1},
};

const static NyxusPixel ibsi_phantom_z2_mask[] = {
{/*x*/1, /*y*/1, 1}, {/*x*/2, /*y*/1, 0}, {/*x*/3, /*y*/1, 1}, {/*x*/4, /*y*/1, 1},
{/*x*/1, /*y*/2, 1}, {/*x*/2, /*y*/2, 1}, {/*x*/3, /*y*/2, 1}, {/*x*/4, /*y*/2, 1},
{/*x*/1, /*y*/3, 1}, {/*x*/2, /*y*/3, 1}, {/*x*/3, /*y*/3, 0}, {/*x*/4, /*y*/3, 1},
{/*x*/1, /*y*/4, 1}, {/*x*/2, /*y*/4, 1}, {/*x*/3, /*y*/4, 1}, {/*x*/4, /*y*/4, 1},
{/*x*/1, /*y*/5, 1}, {/*x*/2, /*y*/5, 1}, {/*x*/3, /*y*/5, 1}, {/*x*/4, /*y*/5, 1},
};

const static NyxusPixel ibsi_phantom_z3_mask[] = {
{/*x*/1, /*y*/1, 1}, {/*x*/2, /*y*/1, 1}, {/*x*/3, /*y*/1, 1}, {/*x*/4, /*y*/1, 1},
{/*x*/1, /*y*/2, 1}, {/*x*/2, /*y*/2, 1}, {/*x*/3, /*y*/2, 1}, {/*x*/4, /*y*/2, 1},
{/*x*/1, /*y*/3, 1}, {/*x*/2, /*y*/3, 1}, {/*x*/3, /*y*/3, 1}, {/*x*/4, /*y*/3, 1},
{/*x*/1, /*y*/4, 1}, {/*x*/2, /*y*/4, 1}, {/*x*/3, /*y*/4, 1}, {/*x*/4, /*y*/4, 1},
{/*x*/1, /*y*/5, 1}, {/*x*/2, /*y*/5, 1}, {/*x*/3, /*y*/5, 1}, {/*x*/4, /*y*/5, 1},
};

const static NyxusPixel ibsi_phantom_z4_mask[] = {
{/*x*/1, /*y*/1, 1}, {/*x*/2, /*y*/1, 1}, {/*x*/3, /*y*/1, 1}, {/*x*/4, /*y*/1, 1},
{/*x*/1, /*y*/2, 1}, {/*x*/2, /*y*/2, 1}, {/*x*/3, /*y*/2, 1}, {/*x*/4, /*y*/2, 1},
{/*x*/1, /*y*/3, 1}, {/*x*/2, /*y*/3, 1}, {/*x*/3, /*y*/3, 1}, {/*x*/4, /*y*/3, 1},
{/*x*/1, /*y*/4, 1}, {/*x*/2, /*y*/4, 1}, {/*x*/3, /*y*/4, 0}, {/*x*/4, /*y*/4, 0},
{/*x*/1, /*y*/5, 1}, {/*x*/2, /*y*/5, 1}, {/*x*/3, /*y*/5, 0}, {/*x*/4, /*y*/5, 0},
};
