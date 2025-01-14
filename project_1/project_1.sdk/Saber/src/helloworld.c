/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include <stdint.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_cache.h"
#include "xtime_l.h"

volatile uint32_t * axi_address_base;

volatile uint32_t CYCLE_COUNT;
volatile uint32_t ARM_CYCLE_COUNT;


void init_INS_keygen(unsigned long long *INS)
{
	int i;
	unsigned long long ins_group[70] =
	{
			/*
			// Timer counter part
			0x0000000000,
			0x0800000000,
			0x0ffffffff1, 	//command_in = {10'd1023,10'd1023,10'd1023,5'd17}; command_we0 = 1; command_we1 = 0;
			0x0800000000,
			0x080000001f,*/


			0x0000000000,
			0x0800000000,
			0x1000200020,
			0x0800000000,
			0x0f00000003,
			0x0700000003,
			0x0800000000,
			0x100ea00020,
			0x08c8007000,
			0x08c8007003,
			0x00c8007003,
			0x0800000000,
			0x0c701a130c,
			0x04701a130c,
			0x0800000000,
			0x09301a200c,
			0x01301a200c,
			0x0800000000,
			0x0a001a470c,
			0x02001a470c,
			0x0800000000,
			0x0c701a198c,
			0x04701a198c,
			0x0800000000,
			0x09981a338c,
			0x01981a338c,
			0x0800000000,
			0x0b381a470c,
			0x03381a470c,
			0x0800000000,
			0x0c701a2d0c,
			0x04701a2d0c,
			0x0800000000,
			0x0ad01a3a0c,
			0x02d01a3a0c,
			0x0800000000,
			0x0ba01a470c,
			0x03a01a470c,
			0x0800000000,
			0x1003000020,
			0x0800000000,
			0x0f08000083,
			0x0708000083,
			0x0800000000,
			0x0f0800708d,
			0x0800000000,
			0x08c9c20c86,
			0x0800000000,
			0x0949c22006,
			0x0800000000,
			0x09c9c23386,
			0x0800000000,
			0x0e10000c87,
			0x0800000000,
			0x10002003e0,
			0x0e08006100,
			0x0e08006101,
			0x0608006101,
			0x0800000000,
			0x080000001f,
			0x0000000000,
			0x0000000000,
			0x0000000000,
			0x0000000000
			};

		for(i=0; i<64; i++)
			INS[i] = ins_group[i];
}

void init_INS_enc(unsigned long long *INS)
{
	int i;
	unsigned long long ins_group[70] =
	{
		0x0000000000,
		0x0800000000,
		0x1000200020,
		0x0800000000,
		0x08f8000f81,
		0x00f8000f81,
		0x0800000000,
		0x10002003e0,
		0x0900000000,
		0x0900000001,
		0x0100000001,
		0x0800000000,
		0x1000400040,
		0x0908000f80,
		0x0908000f82,
		0x0108000f82,
		0x0800000000,
		0x100ea00020,
		0x0990000f00,
		0x0990000f03,
		0x0190000f03,
		0x0800000000,
		0x1003000020,
		0x0800000000,
		0x0d38001103,
		0x0538001103,
		0x0800000000,
		0x0d3800538d,
		0x0800000000,
		0x09914e1906,
		0x0800000000,
		0x0a114e2c86,
		0x0800000000,
		0x0a914e4006,
		0x0800000000,
		0x0e40001907,
		0x0800000000,
		0x0990000009,
		0x0800000000,
		0x09914e190a,
		0x0800000000,
		0x0f303e1908,
		0x0800000000,
		0x1000200440,
		0x0910006400,
		0x0910006401,
		0x0110006401,
		0x0800000000,
		0x1000200040,
		0x0f50001080,
		0x0f50001081,
		0x0750001081,
		0x0800000000,
		0x000000001f,
		0x0000000000,
		0x0000000000,
		0x0000000000,
		0x0000000000,
		0x0000000000,
		0x0000000000,
		0x0000000000,
		0x0000000000,
		0x0000000000,
		0x0000000000
	};

	for(i=0; i<64; i++)
		INS[i] = ins_group[i];
}

void init_INS_dec(unsigned long long *INS)
{
	int i;
	unsigned long long ins_group[70] =
	{
		0x0000000000,
		0x0800000000,
		0x0c00641909,
		0x0800000000,
		0x0c0040400a,
		0x0800000000,
		0x0aa0a0400b,
		0x0800000000,
		0x1000400040,
		0x0ab0002a00,
		0x0ab0002a02,
		0x02b0002a02,
		0x0800000000,
		0x100ea00020,
		0x0ac0000f00,
		0x0ac0000f03,
		0x02c0000f03,
		0x0800000000,
		0x1003000020,
		0x0800000000,
		0x0e68002b83,
		0x0668002b83,
		0x0800000000,
		0x0e6800668d,
		0x0800000000,
		0x0ac19a2c06,
		0x0800000000,
		0x0b419a3f86,
		0x0800000000,
		0x0bc19a5306,
		0x0800000000,
		0x0ec8002c07,
		0x0800000000,
		0x0ac0000009,
		0x0800000000,
		0x0ac19a2c0a,
		0x0800000000,
		0x0fb8a82c08,
		0x0800000000,
		0x1000200440,
		0x0ab8001900,
		0x0ab8001901,
		0x02b8001901,
		0x0800000000,
		0x1000200040,
		0x0fd8002b00,
		0x0fd8002b01,
		0x07d8002b01,
		0x0800000000,

		0x1000000088,
		0x0801b2190e,
		0x0000000000,
		0x0800000000,
		0x0fe1f60f8f,
		0x0000000000,

		0x000000001f,
		0x0000000000,
		0x0000000000,
		0x0000000000,
		0x0000000000,
		0x0000000000,
		0x0000000000,
		0x0000000000,
		0x0000000000
	};

	for(i=0; i<64; i++)
		INS[i] = ins_group[i];
}

void init_tv_keygen(unsigned long long *tv)
{
	int i;
	unsigned long long random_seed[4], random_noiseseed[4], pseudo_random[4];

	random_seed[0] = 0x5e8c154d23501506;
    random_seed[1] = 0x257aef04fe9555c9;
    random_seed[2] = 0x79c42bcc242e7f76;
    random_seed[3] = 0xe7fdbc9adc869dd0;

    random_noiseseed[0] = 0xff6da38dbcbc9f1a;
    random_noiseseed[1] = 0xdb0f17963220be2a;
    random_noiseseed[2] = 0x79b6fc677f29c397;
    random_noiseseed[3] = 0xb05302d09f9c71ac;

    pseudo_random[0] = 0xc4105f43f504f0b2;
	pseudo_random[1] = 0x9bfd7a44481145cd;
	pseudo_random[2] = 0x3ad0e00d7709b299;
	pseudo_random[3] = 0x8c6871e56bbcb7cd;

	/*
	random_seed[0] = 0xb9c04a70a8c38a5a;
	random_seed[1] = 0xcf2af6fbcb05f906;
	random_seed[2] = 0xf9e7247f9f6b0481;
	random_seed[3] = 0xc783d4372ca6435b;
	random_noiseseed[0] = 0x6169fe311ed00f11;
	random_noiseseed[1] = 0x50042a67a0501b42;
	random_noiseseed[2] = 0x62bb21a2a9943815;
	random_noiseseed[3] = 0x65479e58e5d759d0;
	pseudo_random[0] = 0x42ca16a07585aca6;
	pseudo_random[1] = 0x109c2afa9212e90d;
	pseudo_random[2] = 0x62e0c92f82139357;
	pseudo_random[3] = 0x4bc110bcd85ea9a5;
	*/
	/*
	random_seed[0] = 0xf120cc3be922a0cf;
	random_seed[1] = 0x29c569bc77c0deef;
	random_seed[2] = 0x31bc648ad8204eca;
	random_seed[3] = 0xd2f0df852beb3bf4;
	random_noiseseed[0] = 0x1d8cd5d8166220a0;
	random_noiseseed[1] = 0xccd6173e5b52505e;
	random_noiseseed[2] = 0xca67e51d285a86c6;
	random_noiseseed[3] = 0x405e1adaaf227484;
	pseudo_random[0] = 0x897d014b09cbfa0a;
	pseudo_random[1] = 0xead5e4234c09fd2d;
	pseudo_random[2] = 0xdd2d24baff6800ce;
	pseudo_random[3] = 0x295d9604526ba30;
	*/
	// Load random_seed[] in #0-#3
	for(i=0; i<4; i++)
		tv[i] = random_seed[i];

	// Load random_noiseseed[] in #4-#7
	for(i=0; i<4; i++)
		tv[i+4] = random_noiseseed[i];

	// Load pseudo_random[] in #768-#771  (part of sk_CCA)
	for(i=0; i<4; i++)
		tv[i+768] = pseudo_random[i];

	tv[1023] = 0x0100000000;

}

void init_tv_enc(unsigned long long *tv)
{
			int i;

			// pk
			tv[0] = 0xdb0cb67a17a9aeeb;
			tv[1] = 0xaf199f96dfb6e521LL;
			tv[2] = 0xa84c0b05a31f0773LL;
			tv[3] = 0xe4e75a38fe9b7e90LL;
			tv[4] = 0x83063bbf4ab6f1e9LL;
			tv[5] = 0xce24a7d346129d61LL;
			tv[6] = 0x59d86277b5c4932cLL;
			tv[7] = 0xaae8426989a2be47LL;
			tv[8] = 0xa251bafff3b27b1eLL;
			tv[9] = 0xc7a8c333917fd996LL;
			tv[10] = 0x24b5e58de318fd4dLL;
			tv[11] = 0x8405689185e8410eLL;
			tv[12] = 0x5290d19cdf5cc624LL;
			tv[13] = 0x851f72f75a8af802LL;
			tv[14] = 0x7db927f9f2744106LL;
			tv[15] = 0x1fa21f265fce8169LL;
			tv[16] = 0x23b3793bbb74befaLL;

			tv[17] = 0x81a6a605a72248a5LL;
			tv[18] = 0x5c9f7af3d1eec257LL;
			tv[19] = 0x35bac167a6d5a169LL;
			tv[20] = 0xbb371fd2f16fbfd4LL;
			tv[21] = 0x3a4beedd55930e09LL;
			tv[22] = 0xa7b0a138e8cca887LL;
			tv[23] = 0x8b2484b5147a7f6LL;
			tv[24] = 0xdc32a1ccaf64d398LL;
			tv[25] = 0x5d233c0712fb520fLL;
			tv[26] = 0x1b0a1b34037b1f28LL;
			tv[27] = 0x41d6d6dc64eea60bLL;
			tv[28] = 0x6a2a881e47823d38LL;
			tv[29] = 0xa5577542a88e9f95LL;
			tv[30] = 0xd5d4f00565eef0a3LL;
			tv[31] = 0xa9c2feb61f05992cLL;
			tv[32] = 0xa9b826678361734eLL;
			tv[33] = 0x58d0189da858f427LL;
			tv[34] = 0x57e11928fbc29e9fLL;
			tv[35] = 0x298c620bec72976fLL;
			tv[36] = 0xba6aa2ed35fc7de8LL;
			tv[37] = 0x5ba6dcaa966d51dLL;
			tv[38] = 0x5b220964cfcd9c51LL;
			tv[39] = 0x2d0bca433f157618LL;
			tv[40] = 0x9b443aa5a59796efLL;
			tv[41] = 0x4e053fbca7eae146LL;
			tv[42] = 0xa06e088cb63aa85dLL;
			tv[43] = 0xb4e96529328ca9c9LL;
			tv[44] = 0x23c6831bc6526d46LL;
			tv[45] = 0xc9b54ce18ba2ee45LL;
			tv[46] = 0x7660eff71e47456fLL;
			tv[47] = 0x9988a8a73fdfe3afLL;
			tv[48] = 0x88dfbfdcbf322ec6LL;
			tv[49] = 0xa2108c8013456497LL;
			tv[50] = 0xe694eaf738fabf09LL;
			tv[51] = 0xffadb8c39b130facLL;
			tv[52] = 0x3dbe30567436afc4LL;
			tv[53] = 0xfe9c977e773850a7LL;
			tv[54] = 0xdc1c0e4719bdc4c0LL;
			tv[55] = 0x70fb42b2dc86292fLL;
			tv[56] = 0xb90d3b752e33567fLL;
			tv[57] = 0xf1c2879708c1688eLL;
			tv[58] = 0x89521c028e3fb3dbLL;
			tv[59] = 0xe64f2761650d44d6LL;
			tv[60] = 0x3a39c9bf018614ffLL;
			tv[61] = 0x74a2111adfa9501aLL;
			tv[62] = 0xc2e91249f06b8047LL;
			tv[63] = 0x43c98ebae7353c10LL;
			tv[64] = 0x9a9fd7a0aedab432LL;
			tv[65] = 0x46b15709457ead21LL;
			tv[66] = 0x4f5ee67747a43b8dLL;
			tv[67] = 0x3b0d90ce8010b434LL;
			tv[68] = 0x4651a27169eb46cbLL;
			tv[69] = 0xc8e1ac0c1da95bbdLL;
			tv[70] = 0x49e6bcf110623b30LL;
			tv[71] = 0x8ace6110ed92fdccLL;
			tv[72] = 0xe2dee5c889e68f46LL;
			tv[73] = 0xb3c1881af75c2d8cLL;
			tv[74] = 0xd29979b038242fdLL;
			tv[75] = 0x1ccee0025adc23e9LL;
			tv[76] = 0x7a224b5054af6e6fLL;
			tv[77] = 0xf59c794a193c1844LL;
			tv[78] = 0x88bb526a7d01fb70LL;
			tv[79] = 0xdf17b3fdc062f8dfLL;
			tv[80] = 0x999a574c3a5bdbLL;
			tv[81] = 0x6a8a87cda0054723LL;
			tv[82] = 0x8e15cb4b06e9f123LL;
			tv[83] = 0xe93c5f7568e4d792LL;
			tv[84] = 0x6be9930e24d92c6dLL;
			tv[85] = 0xb74b6f234273c6efLL;
			tv[86] = 0x6d95f092a53554feLL;
			tv[87] = 0x63091cc289d970f2LL;
			tv[88] = 0xad42fbb2c95ac65eLL;
			tv[89] = 0xfbada8e389a4d6abLL;
			tv[90] = 0xba727e965ec53bf1LL;
			tv[91] = 0x5eadf50485cccda5LL;
			tv[92] = 0xbc0c8f56ffcc80e1LL;
			tv[93] = 0x45db90d2fe0233cfLL;
			tv[94] = 0xec41cf691281ad11LL;
			tv[95] = 0xf154b1925b0eae9cLL;
			tv[96] = 0xcf29f64d38d2d5c6LL;
			tv[97] = 0xd32f7e54c0da00aaLL;
			tv[98] = 0x33a0d5d7dae3fe7cLL;
			tv[99] = 0xe04d53aecdcc37f6LL;
			tv[100] = 0x17d6873d2a92e609LL;
			tv[101] = 0x5ea55c8852466676LL;
			tv[102] = 0xa966ecabbbab9ab3LL;
			tv[103] = 0xc03d5f482d8271cdLL;
			tv[104] = 0x26bf255968ddf6a0LL;
			tv[105] = 0x7cc02cc25388e434LL;
			tv[106] = 0xdb073db95e3f1ab1LL;
			tv[107] = 0xeae80134639784b9LL;
			tv[108] = 0x3d8770c3fb00716LL;
			tv[109] = 0xb2c01f22fd617eefLL;
			tv[110] = 0xd6952fd92436853aLL;
			tv[111] = 0x90ac47ecb2785e06LL;
			tv[112] = 0x9ec9276bc0dcc123LL;
			tv[113] = 0x914bf667feb54960LL;
			tv[114] = 0xa9ad185c7641e730LL;
			tv[115] = 0x745ceb4a6f29f7beLL;
			tv[116] = 0x2d6bb2da94c195eLL;
			tv[117] = 0xe6e8f10cc636f4f0LL;
			tv[118] = 0xa0cb9fcd5ef9012dLL;
			tv[119] = 0x397ebfc1b53c6f4fLL;
			tv[120] = 0x5ebe66a7a7008807LL;
			tv[121] = 0x83399ee2fcd34a24LL;
			tv[122] = 0x7cf2abaac982fe9cLL;
			tv[123] = 0x8f932d5653c62fcfLL;
			// 4 word random_seed
			tv[124] = 0xb01ad4280719778LL;
			tv[125] = 0xf0dedd135de98bc9LL;
			tv[126] = 0xc7af6f4295ab3365LL;
			tv[127] = 0x6245b7ad99cd7649LL;

			/*
			tv[0] = 0xaa90b8f877e7aa45;
			tv[1] = 0xe401b38d98910420;
			tv[2] = 0x98cd127858eb0b78;
			tv[3] = 0x75b902dd33639f14;
			tv[4] = 0x2986afc8d6754f99;
			tv[5] = 0x30ff483e6bd30061;
			tv[6] = 0x9253912627d793ff;
			tv[7] = 0xd662962a795d7e9d;
			tv[8] = 0xe65cf8ef05efe046;
			tv[9] = 0xf2e77668f8333df5;
			tv[10] = 0x3c112f26e04f274;
			tv[11] = 0x1c77eaf64bba3f96;
			tv[12] = 0x98cb735ce173af40;
			tv[13] = 0x4f5fb8d8b0f23158;
			tv[14] = 0xd4117c6d835c1990;
			tv[15] = 0x70cfaf015a5698c0;
			tv[16] = 0xe427a47da4af2b17;
			tv[17] = 0xa54db4ff93467434;
			tv[18] = 0x944f66009e6c721c;
			tv[19] = 0x22a2c7caa776e380;
			tv[20] = 0xe50a6fd282b6488b;
			tv[21] = 0x602bf5f25d9c8672;
			tv[22] = 0x583ac1c739681585;
			tv[23] = 0xbda441b087989775;
			tv[24] = 0x163c92f70e356976;
			tv[25] = 0x84af4fe3c83aa5c5;
			tv[26] = 0x30bdf23a672ed123;
			tv[27] = 0x60eb8a68989d6413;
			tv[28] = 0x6f8aa5058a3abf89;
			tv[29] = 0x78a74aac8b045cb9;
			tv[30] = 0x79a25a0c5486ab0f;
			tv[31] = 0xfa2c1ff7e9d9f943;
			tv[32] = 0x8de2688e8d61d2f0;
			tv[33] = 0x7e92c79123d8eb33;
			tv[34] = 0x3d6ba54006cc24d7;
			tv[35] = 0xed052fa9b81ee3e;
			tv[36] = 0x9ea6c6c4801da347;
			tv[37] = 0xbd6e9f73f7473fd9;
			tv[38] = 0x6aef823350136216;
			tv[39] = 0xcf02b9a1f91c2da;
			tv[40] = 0xa910933e1cce837f;
			tv[41] = 0xed2d1d03a3f8602b;
			tv[42] = 0x66cd04dcff595e1d;
			tv[43] = 0xf35d3949c29e3cd1;
			tv[44] = 0x4327d785db48096c;
			tv[45] = 0xd11eb7fee9b7955c;
			tv[46] = 0x324fd51926fb97b7;
			tv[47] = 0xd26da27e797b6947;
			tv[48] = 0xf7a40cdfd9de3a17;
			tv[49] = 0xb05307ac80fb7e75;
			tv[50] = 0x900154e6eabe0651;
			tv[51] = 0x94a055fe9907f3a9;
			tv[52] = 0x36b07d7a4545faa5;
			tv[53] = 0xef7e1d5821f3ced8;
			tv[54] = 0x4eec42d88e72d8fc;
			tv[55] = 0xe89335c45f41d69f;
			tv[56] = 0xf42453e47b1d6e2f;
			tv[57] = 0xe77d76687cd0d007;
			tv[58] = 0xc65cbf8f0e0cdb30;
			tv[59] = 0x1ed6f76d6e28161e;
			tv[60] = 0xcf41ae0c2f76001a;
			tv[61] = 0xbdc25e9d908017bb;
			tv[62] = 0x16a9fdae0eab31bb;
			tv[63] = 0x77e5e3a3cd466339;
			tv[64] = 0x8c698bad60a1f1e3;
			tv[65] = 0xc3835e2a01b737bd;
			tv[66] = 0xa7bb5492507338fb;
			tv[67] = 0x548945219e9c65a0;
			tv[68] = 0xc23534df4c2898f9;
			tv[69] = 0xbf5352c258a0e75f;
			tv[70] = 0xc6931141786e4342;
			tv[71] = 0x946b93160c8e82be;
			tv[72] = 0x125f0e7677169a28;
			tv[73] = 0x14e1ed4750a5824e;
			tv[74] = 0x989991e68e4922a1;
			tv[75] = 0x6d175c3b284d7cc6;
			tv[76] = 0x309e6f96492339;
			tv[77] = 0x4749b434bf529c5;
			tv[78] = 0xcb617d80bdddf282;
			tv[79] = 0x7b0a3b88afab3642;
			tv[80] = 0xf8b1384dc208c5ad;
			tv[81] = 0xfce8247307cdba0;
			tv[82] = 0x8fe8babc50111f40;
			tv[83] = 0xd1c59eb5e71d2f57;
			tv[84] = 0x33151f26defb3fb7;
			tv[85] = 0xaab4f24d1765b76a;
			tv[86] = 0x9f5902c7e506c7cf;
			tv[87] = 0xd8f7267917985197;
			tv[88] = 0x4553cd4a56b0f5c1;
			tv[89] = 0x22b7adbc524e4277;
			tv[90] = 0x4f09b5715a4c22c0;
			tv[91] = 0xae057e3096361ac1;
			tv[92] = 0x7a296c528b939ae6;
			tv[93] = 0xfa0039e3cc41ef3d;
			tv[94] = 0xe2b5a2a03fa6ea52;
			tv[95] = 0x664721c4101747d5;
			tv[96] = 0xf04a005c5c83b747;
			tv[97] = 0x5e693686f10ee5c7;
			tv[98] = 0xee96129a0569d834;
			tv[99] = 0xa5df537a0c7950ea;
			tv[100] = 0xd8b3c6f0d2521cfd;
			tv[101] = 0x7431f561b11df8b8;
			tv[102] = 0x7dbaa67be31ff134;
			tv[103] = 0x7f32c1f57ab7fff3;
			tv[104] = 0xf48b020d913135c4;
			tv[105] = 0x7225c562b18998fe;
			tv[106] = 0xd9f393b38d05acec;
			tv[107] = 0x1ade142536b479d8;
			tv[108] = 0x592cffff0ca2452a;
			tv[109] = 0xb7a45e45a8e082d4;
			tv[110] = 0xc854ae50f1eb97e7;
			tv[111] = 0x2fa9b0456ae14aa1;
			tv[112] = 0xb54e7124a5d9b8e5;
			tv[113] = 0x7619134c87c59cf6;
			tv[114] = 0x73053135f555ed02;
			tv[115] = 0x77dffae530d05a95;
			tv[116] = 0xc7add4884058f4e1;
			tv[117] = 0x4e5ba07a6984a4eb;
			tv[118] = 0x64678f110335a618;
			tv[119] = 0x91fc2880fc7e75e2;
			tv[120] = 0x4de133008086236;
			tv[121] = 0x64862bfd8f4e4a63;
			tv[122] = 0x26f4c674cd8ed98c;
			tv[123] = 0xc48bbc8b622faf2d;
			tv[124] = 0x9d67c352bb445264;
			tv[125] = 0x121dafa7977f8d9a;
			tv[126] = 0x9d0ad3abefb2ffe8;
			tv[127] = 0xfe2d9d668f324f46;
			*/
			/*
			tv[0] = 0xf8b882c261f8c182;
			tv[1] = 0xc06a5b3c1f737f72;
			tv[2] = 0xd98cd58e8633b5b7;
			tv[3] = 0xd831cbba2563b3d8;
			tv[4] = 0xb0b5badbcb017071;
			tv[5] = 0x45b8e72303e8949b;
			tv[6] = 0x7beaf4c68dcb9f3c;
			tv[7] = 0x74be829f1d60ad9d;
			tv[8] = 0xc289fef2296fb3aa;
			tv[9] = 0xcb54b3745448cba3;
			tv[10] = 0xc3e8c9475f64cbe9;
			tv[11] = 0x1c3e850f31f291b3;
			tv[12] = 0x60ab5e9a15abb985;
			tv[13] = 0x2e5a1f3736f0ff6e;
			tv[14] = 0xd22cbd7baac960fe;
			tv[15] = 0xf8f2125d95a1a5;
			tv[16] = 0x6da774a7f46ef71f;
			tv[17] = 0xfe29e9f440d5a9bb;
			tv[18] = 0x94f64c3de618c741;
			tv[19] = 0x7060cab998c551b8;
			tv[20] = 0x1c46a2192ef5708b;
			tv[21] = 0xca0f795390e2b15e;
			tv[22] = 0x24e444466b79f4dc;
			tv[23] = 0x774df1a4b17262a1;
			tv[24] = 0x83386f5190fa5665;
			tv[25] = 0x6db739ee290e13c0;
			tv[26] = 0x31537fd3d4f2bf21;
			tv[27] = 0xeaf3eee18e65c618;
			tv[28] = 0x4793e4658fb48fce;
			tv[29] = 0xfb28ab516b4788bf;
			tv[30] = 0xaec97a063923178e;
			tv[31] = 0x66dc36bda837b0fb;
			tv[32] = 0xe3f1622a437ed20e;
			tv[33] = 0x3556430071c47271;
			tv[34] = 0xb12e0e6354d3e93c;
			tv[35] = 0xe24eaa67c892383b;
			tv[36] = 0x55b78f45effd77ab;
			tv[37] = 0x11c0109eda55853f;
			tv[38] = 0x8f66f24c94561938;
			tv[39] = 0x2bcd652b4c7be6f9;
			tv[40] = 0xed4caa8351110805;
			tv[41] = 0x61b56483bf564e2b;
			tv[42] = 0x237d95e20b45b26d;
			tv[43] = 0x5fb7296687737f6b;
			tv[44] = 0x19ca0c9c23cf9ac7;
			tv[45] = 0xc090c24065cfaf3e;
			tv[46] = 0x6d9c2476fc854f9;
			tv[47] = 0xe9e1ad88358eb059;
			tv[48] = 0x6b1714b221ac6c5d;
			tv[49] = 0x73de687097ff52d;
			tv[50] = 0xb7e7546cb4df52a3;
			tv[51] = 0x9ecc289180dc490c;
			tv[52] = 0x64834f108c65d1e0;
			tv[53] = 0x1b23955206d101c9;
			tv[54] = 0x49506d1d1043f46a;
			tv[55] = 0x13ccce870a297c2a;
			tv[56] = 0x7712bab83841679a;
			tv[57] = 0x8ca0dfc51d890240;
			tv[58] = 0xc0ba542f5284649e;
			tv[59] = 0xc00c8a55920da147;
			tv[60] = 0xf17e665be1a189f7;
			tv[61] = 0x8015198825f0d652;
			tv[62] = 0xccb736f60a7aaf34;
			tv[63] = 0xfb71e26db415ba2c;
			tv[64] = 0x4b5d165bcaf8c43a;
			tv[65] = 0xd098f1675570c200;
			tv[66] = 0x3614bb9a4016b567;
			tv[67] = 0xf9289e4a56cc024;
			tv[68] = 0xfaa329823edaa5d3;
			tv[69] = 0x883d26c41cd09ff5;
			tv[70] = 0x9916de1743816843;
			tv[71] = 0x1fd31c7c1c9532fc;
			tv[72] = 0x98e524a44216a69b;
			tv[73] = 0xf9bf2123568a9bd;
			tv[74] = 0xa1c258681e776e46;
			tv[75] = 0x2d1b06461d8f36c;
			tv[76] = 0xa7d8fbe3e492ff2a;
			tv[77] = 0xb41211deb76abbe2;
			tv[78] = 0x925e3dd5a0253c55;
			tv[79] = 0x491c08030a3b05;
			tv[80] = 0xe12d019f747e2446;
			tv[81] = 0xb899a3cbe599e667;
			tv[82] = 0xd45b45e7df738ad;
			tv[83] = 0x16c539bf340b2347;
			tv[84] = 0x29041628fd5dba84;
			tv[85] = 0xe5d3fec221ee2371;
			tv[86] = 0xe1d689861f86a7c4;
			tv[87] = 0x9fb8e4d2e7da8af7;
			tv[88] = 0xcac9cb3958c37a92;
			tv[89] = 0x28f06c4e461d5491;
			tv[90] = 0x93d3341ecc6b4876;
			tv[91] = 0x9f21fd92df88cddb;
			tv[92] = 0xf6c9e04a416780bd;
			tv[93] = 0xf6d8c984713382eb;
			tv[94] = 0x7eb3ce26ff0c7d3b;
			tv[95] = 0x67f4f6e1b301efec;
			tv[96] = 0xd2064703da1db79a;
			tv[97] = 0x1192add5aea09bce;
			tv[98] = 0xe7c1b49d2fdda2b9;
			tv[99] = 0x3001f0b60b83a926;
			tv[100] = 0x80d89e8c2bc693fe;
			tv[101] = 0xa97f043325677b0d;
			tv[102] = 0xa3d260ed127ed87e;
			tv[103] = 0xec8800109fdf7c1a;
			tv[104] = 0xe25253f871eaeec6;
			tv[105] = 0x90a2c054361426fd;
			tv[106] = 0x554d70129ccabead;
			tv[107] = 0xddb330edef111091;
			tv[108] = 0xe4e948e9c9fafada;
			tv[109] = 0x4907b3dee45de1ba;
			tv[110] = 0x133d2180387dc1c;
			tv[111] = 0xa893f3a1f287e8fc;
			tv[112] = 0x1a208bf5b64ec573;
			tv[113] = 0xf3de0bad36411ce4;
			tv[114] = 0x92f06e3a68f21d4d;
			tv[115] = 0xf23365726f48f0a;
			tv[116] = 0x1507265337ac07e3;
			tv[117] = 0x57a3a551eb1ec10d;
			tv[118] = 0x3e69cff009cfc8c5;
			tv[119] = 0xc12041f575b038c3;
			tv[120] = 0x3f9e8999c019239f;
			tv[121] = 0x19a537c9ddd85196;
			tv[122] = 0x56903d39181ac454;
			tv[123] = 0x87acde510c501ac8;
			tv[124] = 0x55db1b3a862a6bde;
			tv[125] = 0x7671fbe9b341bca7;
			tv[126] = 0xae2e96a6a2310560;
			tv[127] = 0x8a63d2a79f0834d0;
			*/

			for(i=128; i<1024; i++)
				tv[i] = 0x0000000000000000;
}


void init_tv_dec(unsigned long long *tv)
{
		int i;

		unsigned long long cpa_secret[48], pk[124], hash_pk[4], pseudo_random[4];
		unsigned long long ct[136];


		cpa_secret[0] = 0x939a1019012a0091;
		cpa_secret[1] = 0x1900922102139ba;
		cpa_secret[2] = 0xba0ba01909010c0a;
		cpa_secret[3] = 0x211099001a990999;
		cpa_secret[4] = 0x9911311100092110;
		cpa_secret[5] = 0x1aa0a191a09191b;
		cpa_secret[6] = 0xab1190109911000;
		cpa_secret[7] = 0xab91110310a20a3;
		cpa_secret[8] = 0x3a14092901a9910a;
		cpa_secret[9] = 0x920909a009032129;
		cpa_secret[10] = 0xa9a1202020b9a11;
		cpa_secret[11] = 0x920001111a00a390;
		cpa_secret[12] = 0x99a00ab10191019;
		cpa_secret[13] = 0x91a02a1aa211911;
		cpa_secret[14] = 0x199090011a2a9199;
		cpa_secret[15] = 0x1900911219210912;
		cpa_secret[16] = 0x1a01019310091009;
		cpa_secret[17] = 0xba3100191b929a11;
		cpa_secret[18] = 0x1021000010a09000;
		cpa_secret[19] = 0xa00a022112aa290b;
		cpa_secret[20] = 0x99229210a1112111;
		cpa_secret[21] = 0x9901010001a0039;
		cpa_secret[22] = 0x2290a92a09911;
		cpa_secret[23] = 0x1191120090100900;
		cpa_secret[24] = 0xa039010029931930;
		cpa_secret[25] = 0x1190009112b12a0a;
		cpa_secret[26] = 0x119a1120013922a;
		cpa_secret[27] = 0x211b1a9a92b9190;
		cpa_secret[28] = 0x1301199910011;
		cpa_secret[29] = 0x10b11220291a9209;
		cpa_secret[30] = 0x1990110021102000;
		cpa_secret[31] = 0xa0911290a9a94a20;
		cpa_secret[32] = 0x1999020aaa0920a;
		cpa_secret[33] = 0x9991122b1a032;
		cpa_secret[34] = 0x11101b209aa11100;
		cpa_secret[35] = 0x1911a029a992b199;
		cpa_secret[36] = 0x1b1a01019001219c;
		cpa_secret[37] = 0x1090a20a9291a901;
		cpa_secret[38] = 0xa909901111a92c1;
		cpa_secret[39] = 0x9a2a9090902a031a;
		cpa_secret[40] = 0xa9009911b09b0a29;
		cpa_secret[41] = 0x9000109199aa1b1a;
		cpa_secret[42] = 0xa09a0a1111391210;
		cpa_secret[43] = 0x110901119101999a;
		cpa_secret[44] = 0xa011011a10212919;
		cpa_secret[45] = 0x201111001932012;
		cpa_secret[46] = 0xa9aa99a010912a19;
		cpa_secret[47] = 0x21a9019919a0a902;

		// 120+4 word pk; last 4 words are hash(pk)
		pk[0] = 0xdb0cb67a17a9aeeb;
		pk[1] = 0xaf199f96dfb6e521;
		pk[2] = 0xa84c0b05a31f0773;
		pk[3] = 0xe4e75a38fe9b7e90;
		pk[4] = 0x83063bbf4ab6f1e9;
		pk[5] = 0xce24a7d346129d61;
		pk[6] = 0x59d86277b5c4932c;
		pk[7] = 0xaae8426989a2be47;
		pk[8] = 0xa251bafff3b27b1e;
		pk[9] = 0xc7a8c333917fd996;
		pk[10] = 0x24b5e58de318fd4d;
		pk[11] = 0x8405689185e8410e;
		pk[12] = 0x5290d19cdf5cc624;
		pk[13] = 0x851f72f75a8af802;
		pk[14] = 0x7db927f9f2744106;
		pk[15] = 0x1fa21f265fce8169;
		pk[16] = 0x23b3793bbb74befa;
		pk[17] = 0x81a6a605a72248a5;
		pk[18] = 0x5c9f7af3d1eec257;
		pk[19] = 0x35bac167a6d5a169;
		pk[20] = 0xbb371fd2f16fbfd4;
		pk[21] = 0x3a4beedd55930e09;
		pk[22] = 0xa7b0a138e8cca887;
		pk[23] = 0x8b2484b5147a7f6;
		pk[24] = 0xdc32a1ccaf64d398;
		pk[25] = 0x5d233c0712fb520f;
		pk[26] = 0x1b0a1b34037b1f28;
		pk[27] = 0x41d6d6dc64eea60b;
		pk[28] = 0x6a2a881e47823d38;
		pk[29] = 0xa5577542a88e9f95;
		pk[30] = 0xd5d4f00565eef0a3;
		pk[31] = 0xa9c2feb61f05992c;
		pk[32] = 0xa9b826678361734e;
		pk[33] = 0x58d0189da858f427;
		pk[34] = 0x57e11928fbc29e9f;
		pk[35] = 0x298c620bec72976f;
		pk[36] = 0xba6aa2ed35fc7de8;
		pk[37] = 0x5ba6dcaa966d51d;
		pk[38] = 0x5b220964cfcd9c51;
		pk[39] = 0x2d0bca433f157618;
		pk[40] = 0x9b443aa5a59796ef;
		pk[41] = 0x4e053fbca7eae146;
		pk[42] = 0xa06e088cb63aa85d;
		pk[43] = 0xb4e96529328ca9c9;
		pk[44] = 0x23c6831bc6526d46;
		pk[45] = 0xc9b54ce18ba2ee45;
		pk[46] = 0x7660eff71e47456f;
		pk[47] = 0x9988a8a73fdfe3af;
		pk[48] = 0x88dfbfdcbf322ec6;
		pk[49] = 0xa2108c8013456497;
		pk[50] = 0xe694eaf738fabf09;
		pk[51] = 0xffadb8c39b130fac;
		pk[52] = 0x3dbe30567436afc4;
		pk[53] = 0xfe9c977e773850a7;
		pk[54] = 0xdc1c0e4719bdc4c0;
		pk[55] = 0x70fb42b2dc86292f;
		pk[56] = 0xb90d3b752e33567f;
		pk[57] = 0xf1c2879708c1688e;
		pk[58] = 0x89521c028e3fb3db;
		pk[59] = 0xe64f2761650d44d6;
		pk[60] = 0x3a39c9bf018614ff;
		pk[61] = 0x74a2111adfa9501a;
		pk[62] = 0xc2e91249f06b8047;
		pk[63] = 0x43c98ebae7353c10;
		pk[64] = 0x9a9fd7a0aedab432;
		pk[65] = 0x46b15709457ead21;
		pk[66] = 0x4f5ee67747a43b8d;
		pk[67] = 0x3b0d90ce8010b434;
		pk[68] = 0x4651a27169eb46cb;
		pk[69] = 0xc8e1ac0c1da95bbd;
		pk[70] = 0x49e6bcf110623b30;
		pk[71] = 0x8ace6110ed92fdcc;
		pk[72] = 0xe2dee5c889e68f46;
		pk[73] = 0xb3c1881af75c2d8c;
		pk[74] = 0xd29979b038242fd;
		pk[75] = 0x1ccee0025adc23e9;
		pk[76] = 0x7a224b5054af6e6f;
		pk[77] = 0xf59c794a193c1844;
		pk[78] = 0x88bb526a7d01fb70;
		pk[79] = 0xdf17b3fdc062f8df;
		pk[80] = 0x999a574c3a5bdb;
		pk[81] = 0x6a8a87cda0054723;
		pk[82] = 0x8e15cb4b06e9f123;
		pk[83] = 0xe93c5f7568e4d792;
		pk[84] = 0x6be9930e24d92c6d;
		pk[85] = 0xb74b6f234273c6ef;
		pk[86] = 0x6d95f092a53554fe;
		pk[87] = 0x63091cc289d970f2;
		pk[88] = 0xad42fbb2c95ac65e;
		pk[89] = 0xfbada8e389a4d6ab;
		pk[90] = 0xba727e965ec53bf1;
		pk[91] = 0x5eadf50485cccda5;
		pk[92] = 0xbc0c8f56ffcc80e1;
		pk[93] = 0x45db90d2fe0233cf;
		pk[94] = 0xec41cf691281ad11;
		pk[95] = 0xf154b1925b0eae9c;
		pk[96] = 0xcf29f64d38d2d5c6;
		pk[97] = 0xd32f7e54c0da00aa;
		pk[98] = 0x33a0d5d7dae3fe7c;
		pk[99] = 0xe04d53aecdcc37f6;
		pk[100] = 0x17d6873d2a92e609;
		pk[101] = 0x5ea55c8852466676;
		pk[102] = 0xa966ecabbbab9ab3;
		pk[103] = 0xc03d5f482d8271cd;
		pk[104] = 0x26bf255968ddf6a0;
		pk[105] = 0x7cc02cc25388e434;
		pk[106] = 0xdb073db95e3f1ab1;
		pk[107] = 0xeae80134639784b9;
		pk[108] = 0x3d8770c3fb00716;
		pk[109] = 0xb2c01f22fd617eef;
		pk[110] = 0xd6952fd92436853a;
		pk[111] = 0x90ac47ecb2785e06;
		pk[112] = 0x9ec9276bc0dcc123;
		pk[113] = 0x914bf667feb54960;
		pk[114] = 0xa9ad185c7641e730;
		pk[115] = 0x745ceb4a6f29f7be;
		pk[116] = 0x2d6bb2da94c195e;
		pk[117] = 0xe6e8f10cc636f4f0;
		pk[118] = 0xa0cb9fcd5ef9012d;
		pk[119] = 0x397ebfc1b53c6f4f;
		// Next 4 wrds are seed of [A]
		pk[120] = 0x5ebe66a7a7008807;
		pk[121] = 0x83399ee2fcd34a24;
		pk[122] = 0x7cf2abaac982fe9c;
		pk[123] = 0x8f932d5653c62fcf;

		// Hash of pk
		hash_pk[0] = 0xe997cebe731479ba;
		hash_pk[1] = 0x187b3987e68bf1ac;
		hash_pk[2] = 0x55f3974eaa4b7660;
		hash_pk[3] = 0xc33a00cac8f0a7df;

		// used to output when ct verification fails
		pseudo_random[0] = 0xc4105f43f504f0b2;
		pseudo_random[1] = 0x9bfd7a44481145cd;
		pseudo_random[2] = 0x3ad0e00d7709b299;
		pseudo_random[3] = 0x8c6871e56bbcb7cd;


		ct[0] = 0x93ef29bf4b2b5d4d;
		ct[1] = 0x7c76470f30174362;
		ct[2] = 0x63cd1cf00a2aa8a3;
		ct[3] = 0xee31ef29644057f2;
		ct[4] = 0x84bb0b7613676b39;
		ct[5] = 0x1090c640a94405b4;
		ct[6] = 0xfac0320d07c611ad;
		ct[7] = 0xf3510dc560bc2a8d;
		ct[8] = 0xcf60f25409c506e6;
		ct[9] = 0x7543d7971dfd0bbb;
		ct[10] = 0xfc429b057eb826e6;
		ct[11] = 0x7020a01e08e2bedf;
		ct[12] = 0x5cae8760dce633b;
		ct[13] = 0xfeb492dba0db1927;
		ct[14] = 0x1f7a8562baab9059;
		ct[15] = 0xb212fa63ff6319aa;
		ct[16] = 0x802cc5f210723f3f;
		ct[17] = 0x233f74d643095029;
		ct[18] = 0x3f89c98e3d78731;
		ct[19] = 0xf556523bf4d3862f;
		ct[20] = 0x5e452708c0ba50c2;
		ct[21] = 0x1a5fc705ddf754d8;
		ct[22] = 0xe2761f1c573fb37c;
		ct[23] = 0xbde40ce712f94c0d;
		ct[24] = 0x1161ddea4894754a;
		ct[25] = 0xeba53c8b0f27fe9b;
		ct[26] = 0xe8441ffc80544a80;
		ct[27] = 0x6eb8ba766df2014b;
		ct[28] = 0xf5f28a65aeeb75ff;
		ct[29] = 0xb231f35a623e8c8a;
		ct[30] = 0xeb2163af655f3439;
		ct[31] = 0x694ee07a18dc45cd;
		ct[32] = 0xc6d01c6c028872ab;
		ct[33] = 0x770062b633913786;
		ct[34] = 0x351849cf8595cc9;
		ct[35] = 0xc092dc322d2c5153;
		ct[36] = 0x574ce2b6d4561214;
		ct[37] = 0x52e5576686bfc244;
		ct[38] = 0x44c6ce33067af509;
		ct[39] = 0xc454fea9910fbd3e;
		ct[40] = 0xe140f4cf979b1a43;
		ct[41] = 0xd6cbe0b3b04f077d;
		ct[42] = 0x4b85178d50b40447;
		ct[43] = 0x2c5f5b7470af913a;
		ct[44] = 0xdd0c42195968ab0a;
		ct[45] = 0xd975ae14d4604850;
		ct[46] = 0xa924839e0e9dd21f;
		ct[47] = 0x1c7d2ccb8b44e1d0;
		ct[48] = 0xd8589425c76d1225;
		ct[49] = 0x6a17b725ca2a52f0;
		ct[50] = 0x5563fa636638b515;
		ct[51] = 0x6be475368ced8189;
		ct[52] = 0xd1575704c8271785;
		ct[53] = 0x468347181e2a3d25;
		ct[54] = 0x4de30b4c46496272;
		ct[55] = 0xb42c53765d9815a7;
		ct[56] = 0x8f8d6b3a2b9d4c7;
		ct[57] = 0xeba87e992870546b;
		ct[58] = 0x50d9b82e538be47e;
		ct[59] = 0xf0d8d31504e8e37b;
		ct[60] = 0x39fa56ee34bf8b2b;
		ct[61] = 0xb7002bd57e0e1b9f;
		ct[62] = 0x31a3d0e413986bf6;
		ct[63] = 0xc09511411d738a98;
		ct[64] = 0xca354d9e520e9711;
		ct[65] = 0x50a82b650361486;
		ct[66] = 0x6431e72e606d6a3;
		ct[67] = 0xc92743400d645927;
		ct[68] = 0x6c8d95fd669f5b28;
		ct[69] = 0x362115f49b4439ad;
		ct[70] = 0x61526dd825c5be44;
		ct[71] = 0xe72db3842bd1d1f2;
		ct[72] = 0xca20f758df0a039;
		ct[73] = 0xb20e0949074af8d1;
		ct[74] = 0x1ccdd5f862959fa7;
		ct[75] = 0xf6e9981e3c1148c6;
		ct[76] = 0x4b7bc5c5de2d4326;
		ct[77] = 0xb954e7d771f7ff17;
		ct[78] = 0x280b70b80b8f18b0;
		ct[79] = 0xc0e4b8aacb1d97cc;
		ct[80] = 0x301897ee8c24f456;
		ct[81] = 0xebe266d731857b35;
		ct[82] = 0x1d24ac7833498d95;
		ct[83] = 0xb7674e05c80b1205;
		ct[84] = 0x28d7788316d8a450;
		ct[85] = 0xa1f4f416cb74d61e;
		ct[86] = 0xeaf29f043c5d5ab4;
		ct[87] = 0x7c715c1f494a5b52;
		ct[88] = 0xcc31367740604c11;
		ct[89] = 0x58472d2310542955;
		ct[90] = 0x119a66f3f65a748d;
		ct[91] = 0x12145ac5c731eee9;
		ct[92] = 0x59f2df7d283d5a30;
		ct[93] = 0x89268b0f865aa71d;
		ct[94] = 0xdbd7ed728799bd3b;
		ct[95] = 0xc65c4bd80bf41357;
		ct[96] = 0xb5be4cf82c8fa1b;
		ct[97] = 0xdf4782511d6fc3b8;
		ct[98] = 0x7e5e9bdc9ba66c72;
		ct[99] = 0x72c0e3977940cc9c;
		ct[100] = 0x708be7ecda03a787;
		ct[101] = 0x59ba3eca5729b422;
		ct[102] = 0xbcd01e446c8fcf19;
		ct[103] = 0x1fe777dc75b44f57;
		ct[104] = 0x5ffb14c6980b693e;
		ct[105] = 0xa3cb5f00ebbf1549;
		ct[106] = 0xa49544c9e180b6ba;
		ct[107] = 0x6c87c40015abd1b8;
		ct[108] = 0x3c695eb8782c3219;
		ct[109] = 0x16f2e34df36d9736;
		ct[110] = 0x52faf3bea8d10eec;
		ct[111] = 0x6340946395fac57;
		ct[112] = 0xa21a757caebfc4ee;
		ct[113] = 0xb0f8f7b32032521;
		ct[114] = 0x4a14193db7b3278b;
		ct[115] = 0x8d67594d28da217c;
		ct[116] = 0x9f93435b061571cd;
		ct[117] = 0x105988e51647ddfd;
		ct[118] = 0xdc28501da33026c6;
		ct[119] = 0xc9ffd7b8b534de04;
		ct[120] = 0xd0fdb0fe18120405;
		ct[121] = 0xf84520e69051234c;
		ct[122] = 0xeea41ad5212eef72;
		ct[123] = 0x1d63eee082d1ad8f;
		ct[124] = 0xfa0ae90754535e13;
		ct[125] = 0xbfa3e43692f62432;
		ct[126] = 0xd8a21d509f9a23ee;
		ct[127] = 0x52ceee21fd078507;
		ct[128] = 0xd9f14046e6b44f5e;
		ct[129] = 0x8b416093263cdd95;
		ct[130] = 0x8d30666592ee88ff;
		ct[131] = 0xd23177b71dea55fa;
		ct[132] = 0x29c87a8c9bb254eb;
		ct[133] = 0xc00dc527e92f4a5e;
		ct[134] = 0xc7095ee82da6ddbb;
		ct[135] = 0xc197e2d62be1c3a; // correct is 0xc197e2d62be1c3a;

		/*
		pk[0] = 0xaa90b8f877e7aa45;
		pk[1] = 0xe401b38d98910420;
		pk[2] = 0x98cd127858eb0b78;
		pk[3] = 0x75b902dd33639f14;
		pk[4] = 0x2986afc8d6754f99;
		pk[5] = 0x30ff483e6bd30061;
		pk[6] = 0x9253912627d793ff;
		pk[7] = 0xd662962a795d7e9d;
		pk[8] = 0xe65cf8ef05efe046;
		pk[9] = 0xf2e77668f8333df5;
		pk[10] = 0x3c112f26e04f274;
		pk[11] = 0x1c77eaf64bba3f96;
		pk[12] = 0x98cb735ce173af40;
		pk[13] = 0x4f5fb8d8b0f23158;
		pk[14] = 0xd4117c6d835c1990;
		pk[15] = 0x70cfaf015a5698c0;
		pk[16] = 0xe427a47da4af2b17;
		pk[17] = 0xa54db4ff93467434;
		pk[18] = 0x944f66009e6c721c;
		pk[19] = 0x22a2c7caa776e380;
		pk[20] = 0xe50a6fd282b6488b;
		pk[21] = 0x602bf5f25d9c8672;
		pk[22] = 0x583ac1c739681585;
		pk[23] = 0xbda441b087989775;
		pk[24] = 0x163c92f70e356976;
		pk[25] = 0x84af4fe3c83aa5c5;
		pk[26] = 0x30bdf23a672ed123;
		pk[27] = 0x60eb8a68989d6413;
		pk[28] = 0x6f8aa5058a3abf89;
		pk[29] = 0x78a74aac8b045cb9;
		pk[30] = 0x79a25a0c5486ab0f;
		pk[31] = 0xfa2c1ff7e9d9f943;
		pk[32] = 0x8de2688e8d61d2f0;
		pk[33] = 0x7e92c79123d8eb33;
		pk[34] = 0x3d6ba54006cc24d7;
		pk[35] = 0xed052fa9b81ee3e;
		pk[36] = 0x9ea6c6c4801da347;
		pk[37] = 0xbd6e9f73f7473fd9;
		pk[38] = 0x6aef823350136216;
		pk[39] = 0xcf02b9a1f91c2da;
		pk[40] = 0xa910933e1cce837f;
		pk[41] = 0xed2d1d03a3f8602b;
		pk[42] = 0x66cd04dcff595e1d;
		pk[43] = 0xf35d3949c29e3cd1;
		pk[44] = 0x4327d785db48096c;
		pk[45] = 0xd11eb7fee9b7955c;
		pk[46] = 0x324fd51926fb97b7;
		pk[47] = 0xd26da27e797b6947;
		pk[48] = 0xf7a40cdfd9de3a17;
		pk[49] = 0xb05307ac80fb7e75;
		pk[50] = 0x900154e6eabe0651;
		pk[51] = 0x94a055fe9907f3a9;
		pk[52] = 0x36b07d7a4545faa5;
		pk[53] = 0xef7e1d5821f3ced8;
		pk[54] = 0x4eec42d88e72d8fc;
		pk[55] = 0xe89335c45f41d69f;
		pk[56] = 0xf42453e47b1d6e2f;
		pk[57] = 0xe77d76687cd0d007;
		pk[58] = 0xc65cbf8f0e0cdb30;
		pk[59] = 0x1ed6f76d6e28161e;
		pk[60] = 0xcf41ae0c2f76001a;
		pk[61] = 0xbdc25e9d908017bb;
		pk[62] = 0x16a9fdae0eab31bb;
		pk[63] = 0x77e5e3a3cd466339;
		pk[64] = 0x8c698bad60a1f1e3;
		pk[65] = 0xc3835e2a01b737bd;
		pk[66] = 0xa7bb5492507338fb;
		pk[67] = 0x548945219e9c65a0;
		pk[68] = 0xc23534df4c2898f9;
		pk[69] = 0xbf5352c258a0e75f;
		pk[70] = 0xc6931141786e4342;
		pk[71] = 0x946b93160c8e82be;
		pk[72] = 0x125f0e7677169a28;
		pk[73] = 0x14e1ed4750a5824e;
		pk[74] = 0x989991e68e4922a1;
		pk[75] = 0x6d175c3b284d7cc6;
		pk[76] = 0x309e6f96492339;
		pk[77] = 0x4749b434bf529c5;
		pk[78] = 0xcb617d80bdddf282;
		pk[79] = 0x7b0a3b88afab3642;
		pk[80] = 0xf8b1384dc208c5ad;
		pk[81] = 0xfce8247307cdba0;
		pk[82] = 0x8fe8babc50111f40;
		pk[83] = 0xd1c59eb5e71d2f57;
		pk[84] = 0x33151f26defb3fb7;
		pk[85] = 0xaab4f24d1765b76a;
		pk[86] = 0x9f5902c7e506c7cf;
		pk[87] = 0xd8f7267917985197;
		pk[88] = 0x4553cd4a56b0f5c1;
		pk[89] = 0x22b7adbc524e4277;
		pk[90] = 0x4f09b5715a4c22c0;
		pk[91] = 0xae057e3096361ac1;
		pk[92] = 0x7a296c528b939ae6;
		pk[93] = 0xfa0039e3cc41ef3d;
		pk[94] = 0xe2b5a2a03fa6ea52;
		pk[95] = 0x664721c4101747d5;
		pk[96] = 0xf04a005c5c83b747;
		pk[97] = 0x5e693686f10ee5c7;
		pk[98] = 0xee96129a0569d834;
		pk[99] = 0xa5df537a0c7950ea;
		pk[100] = 0xd8b3c6f0d2521cfd;
		pk[101] = 0x7431f561b11df8b8;
		pk[102] = 0x7dbaa67be31ff134;
		pk[103] = 0x7f32c1f57ab7fff3;
		pk[104] = 0xf48b020d913135c4;
		pk[105] = 0x7225c562b18998fe;
		pk[106] = 0xd9f393b38d05acec;
		pk[107] = 0x1ade142536b479d8;
		pk[108] = 0x592cffff0ca2452a;
		pk[109] = 0xb7a45e45a8e082d4;
		pk[110] = 0xc854ae50f1eb97e7;
		pk[111] = 0x2fa9b0456ae14aa1;
		pk[112] = 0xb54e7124a5d9b8e5;
		pk[113] = 0x7619134c87c59cf6;
		pk[114] = 0x73053135f555ed02;
		pk[115] = 0x77dffae530d05a95;
		pk[116] = 0xc7add4884058f4e1;
		pk[117] = 0x4e5ba07a6984a4eb;
		pk[118] = 0x64678f110335a618;
		pk[119] = 0x91fc2880fc7e75e2;
		pk[120] = 0x4de133008086236;
		pk[121] = 0x64862bfd8f4e4a63;
		pk[122] = 0x26f4c674cd8ed98c;
		pk[123] = 0xc48bbc8b622faf2d;
		cpa_secret[0] = 0x1390999a90020911;
		cpa_secret[1] = 0x2091b1a00001210;
		cpa_secret[2] = 0xb99299aa120010aa;
		cpa_secret[3] = 0xa1a2901090a12903;
		cpa_secret[4] = 0x21092209102b2a29;
		cpa_secret[5] = 0x11021b0101909a9;
		cpa_secret[6] = 0xa901109a9a119001;
		cpa_secret[7] = 0x1a2130100100a921;
		cpa_secret[8] = 0x1ab00900900a19b1;
		cpa_secret[9] = 0x2010911109109a21;
		cpa_secret[10] = 0x91009020b3001c20;
		cpa_secret[11] = 0x9922091a1b119990;
		cpa_secret[12] = 0x211931109a10a10a;
		cpa_secret[13] = 0xa120010191199093;
		cpa_secret[14] = 0x92012aaa09910;
		cpa_secret[15] = 0x19919a9999921200;
		cpa_secret[16] = 0x2012119222202110;
		cpa_secret[17] = 0x122990a192aaa1a0;
		cpa_secret[18] = 0x19029220202029c;
		cpa_secret[19] = 0x920011910999099a;
		cpa_secret[20] = 0xab2201a9b0a39200;
		cpa_secret[21] = 0x1219ba11aaa9a919;
		cpa_secret[22] = 0x23110092900920;
		cpa_secret[23] = 0xa1a0121b1099922;
		cpa_secret[24] = 0xa90199000211001;
		cpa_secret[25] = 0x11911aa00211a910;
		cpa_secret[26] = 0xb99912a290223191;
		cpa_secret[27] = 0x21aa299a13030a1;
		cpa_secret[28] = 0x23201a9099910a1b;
		cpa_secret[29] = 0x91a911ab90b0a090;
		cpa_secret[30] = 0xb9990102191190a1;
		cpa_secret[31] = 0x929a1ba109011a1;
		cpa_secret[32] = 0x10a0009900012191;
		cpa_secret[33] = 0xaa33a9091b210311;
		cpa_secret[34] = 0x9a9ba19991a13999;
		cpa_secret[35] = 0xa090a0020ab1a00b;
		cpa_secret[36] = 0xaaa1001910a190a;
		cpa_secret[37] = 0x190ba01911190002;
		cpa_secret[38] = 0x901ca92019201199;
		cpa_secret[39] = 0x1a9119993991ba90;
		cpa_secret[40] = 0xa9001002a1001100;
		cpa_secret[41] = 0x2910000902090230;
		cpa_secret[42] = 0x1000112aab101100;
		cpa_secret[43] = 0x990901092120923b;
		cpa_secret[44] = 0x19ba010090091a99;
		cpa_secret[45] = 0x9a900209029a101;
		cpa_secret[46] = 0x220301a2001909;
		cpa_secret[47] = 0xb1300929a0a00210;
		hash_pk[0] = 0x98d7232e6c184937;
		hash_pk[1] = 0x2615e42a80aab2e7;
		hash_pk[2] = 0x59fc0ac7ed7d21d7;
		hash_pk[3] = 0xf660580a9d89ca99;
		pseudo_random[0] = 0x42ca16a07585aca6;
		pseudo_random[1] = 0x109c2afa9212e90d;
		pseudo_random[2] = 0x62e0c92f82139357;
		pseudo_random[3] = 0x4bc110bcd85ea9a5;
		ct[0] = 0x9880a7730f964b91;
		ct[1] = 0x143b7e752bc49dc6;
		ct[2] = 0xe6272ef3c2457711;
		ct[3] = 0x3afb14f0cb0c42e6;
		ct[4] = 0x746146d961b5a334;
		ct[5] = 0x6ac40f154b24d5d1;
		ct[6] = 0xb0d1d9a09cb52a5;
		ct[7] = 0x186e38af241c5641;
		ct[8] = 0x5e0fb08d0e13b94e;
		ct[9] = 0xc4556f0e7288f855;
		ct[10] = 0xde7ec2057bed5228;
		ct[11] = 0xd37ffc2d70a6bfc6;
		ct[12] = 0x6203557b77309ba9;
		ct[13] = 0x7df1d60cb99932c6;
		ct[14] = 0x94de3cc20a9e941c;
		ct[15] = 0x19eaf06c8f6bae67;
		ct[16] = 0x980631ea5ce79b1f;
		ct[17] = 0x427eec28dab1e5c3;
		ct[18] = 0x52eb64fe66fdf01f;
		ct[19] = 0xf7913738d7210cfc;
		ct[20] = 0x2b3542b3e8d15091;
		ct[21] = 0xa619c7e836f2be60;
		ct[22] = 0x15ff7c57035a3f68;
		ct[23] = 0x72ed23ed28e3fa6d;
		ct[24] = 0xbd67a3c3400ca2bb;
		ct[25] = 0x9c0c0ad668e73051;
		ct[26] = 0xefa2cfa4c393e8fb;
		ct[27] = 0x628f9e0c0116d5a1;
		ct[28] = 0x830a641825ef66c4;
		ct[29] = 0x95a75f957813d3e8;
		ct[30] = 0xcef0f037156f9e8;
		ct[31] = 0x919a438fb3b7b8b0;
		ct[32] = 0x170cee154ca84247;
		ct[33] = 0xd380e3c530bdb158;
		ct[34] = 0x4d6b11d5fc7da645;
		ct[35] = 0x78515885e65463a2;
		ct[36] = 0x1e619be98e409650;
		ct[37] = 0x1b4132866902fd5c;
		ct[38] = 0xf51271ea7fc80ac;
		ct[39] = 0xb23eb4678a51763c;
		ct[40] = 0x46801d16e5e45b51;
		ct[41] = 0xca95c6131a51ba16;
		ct[42] = 0x2a8f7b280454e098;
		ct[43] = 0x19591e899dda4a99;
		ct[44] = 0xa8bd9e8affad1ecd;
		ct[45] = 0xc0d012d0e8456d3b;
		ct[46] = 0xc8981181aa95e45d;
		ct[47] = 0x2006cf644c8b81bd;
		ct[48] = 0x84dae297a7f6363f;
		ct[49] = 0xd6047ded56b3f7d5;
		ct[50] = 0x69967a14408fe9bf;
		ct[51] = 0xfa9e7b38271ee2a8;
		ct[52] = 0x491897a6d83ecd75;
		ct[53] = 0x73c652ee6802f4a9;
		ct[54] = 0x24a597b2eeb80172;
		ct[55] = 0xd8d11a052d8482b6;
		ct[56] = 0x5fd5d3fd4dd08848;
		ct[57] = 0x84edacb0c1478e98;
		ct[58] = 0xc2f1f5d638508b2;
		ct[59] = 0xf327ea6b8506fd59;
		ct[60] = 0x12881915d2a1dc4b;
		ct[61] = 0x7792af42f88062e6;
		ct[62] = 0x1e82605494f24d1b;
		ct[63] = 0xa60fb7831fc1084b;
		ct[64] = 0x33ef4fe11bdc777c;
		ct[65] = 0x2f68e6dd6edff08f;
		ct[66] = 0x40f76115a19d0af0;
		ct[67] = 0x7ca03c36f4442345;
		ct[68] = 0x41e92d9313a549c8;
		ct[69] = 0x5835288f74c62005;
		ct[70] = 0x28c20a89b38a19cc;
		ct[71] = 0xfab20b5cfa621e0a;
		ct[72] = 0xf51e700443918270;
		ct[73] = 0x8a479c31a1a1ad92;
		ct[74] = 0xc09ab6daa1018987;
		ct[75] = 0xde1b771a530e4820;
		ct[76] = 0xd6e9491fc8c79332;
		ct[77] = 0xec1f3f2b0247c2b7;
		ct[78] = 0xf564859238d86f0d;
		ct[79] = 0xc04e2bbd76f88ce8;
		ct[80] = 0x6bcb47fbcef1485c;
		ct[81] = 0xea4167d07863ac1e;
		ct[82] = 0x3b5fb0c5bc09b2f9;
		ct[83] = 0x8b41368d6bdf29de;
		ct[84] = 0xd19855730922be11;
		ct[85] = 0x65816ef524e0d3f2;
		ct[86] = 0x7a7bb251716f7053;
		ct[87] = 0x706007e7da7da53a;
		ct[88] = 0xec8b57b827933d0d;
		ct[89] = 0x87d159e8e7c71767;
		ct[90] = 0x1edc19d31d9875a8;
		ct[91] = 0x26cad294de7fd4e4;
		ct[92] = 0x4938590dede3f01a;
		ct[93] = 0xf5f8abeed615371d;
		ct[94] = 0x5f25ff94787010e9;
		ct[95] = 0x1a0666791131bff;
		ct[96] = 0x10c9fbc15dc15e39;
		ct[97] = 0x3c4704c3c169dc2a;
		ct[98] = 0x3b8e5a0c0d67d412;
		ct[99] = 0x7ff08c954b9041e5;
		ct[100] = 0xc76993644e922adc;
		ct[101] = 0x80577edd29704274;
		ct[102] = 0x8e000933e2e10a7;
		ct[103] = 0x6288e20346f17e75;
		ct[104] = 0xe49cd4010eb0b9c3;
		ct[105] = 0xf0138c5f81a36501;
		ct[106] = 0xc7c864a477da30bf;
		ct[107] = 0x5f95faf7ea5be19c;
		ct[108] = 0x16b998734bbbf722;
		ct[109] = 0x9732d1678171d57f;
		ct[110] = 0xae2ee8a28085f3db;
		ct[111] = 0xed08fe53141c1631;
		ct[112] = 0xdb349678d0fad12f;
		ct[113] = 0xfdaae53a3c564aea;
		ct[114] = 0xac471e44d3ef6547;
		ct[115] = 0xc2cf019edeef1429;
		ct[116] = 0x2a297511b079a919;
		ct[117] = 0xd38ab62727428509;
		ct[118] = 0x40eca437315bcd13;
		ct[119] = 0xf90785f2d3bbe6fb;
		ct[120] = 0x2e341054a9c544d0;
		ct[121] = 0x1fc36713bf4c2132;
		ct[122] = 0x8f991853bf6c55ce;
		ct[123] = 0xc315628e56199b67;
		ct[124] = 0x9cfa7fc78ab359b3;
		ct[125] = 0x9d8847403f6131ff;
		ct[126] = 0xaefbcfb434b7c103;
		ct[127] = 0xbbd84059c3bd75b3;
		ct[128] = 0x16c62eeb1e038eff;
		ct[129] = 0x2deb9e974079738c;
		ct[130] = 0x58668545e948be28;
		ct[131] = 0x6853977e56f930b2;
		ct[132] = 0x3c35e5f78f849620;
		ct[133] = 0xc38da33e63db119c;
		ct[134] = 0x32429abf0448eb79;
		ct[135] = 0xc4d22acb5636e5ce;
		*/
		/*
		pk[0] = 0xf8b882c261f8c182;
		pk[1] = 0xc06a5b3c1f737f72;
		pk[2] = 0xd98cd58e8633b5b7;
		pk[3] = 0xd831cbba2563b3d8;
		pk[4] = 0xb0b5badbcb017071;
		pk[5] = 0x45b8e72303e8949b;
		pk[6] = 0x7beaf4c68dcb9f3c;
		pk[7] = 0x74be829f1d60ad9d;
		pk[8] = 0xc289fef2296fb3aa;
		pk[9] = 0xcb54b3745448cba3;
		pk[10] = 0xc3e8c9475f64cbe9;
		pk[11] = 0x1c3e850f31f291b3;
		pk[12] = 0x60ab5e9a15abb985;
		pk[13] = 0x2e5a1f3736f0ff6e;
		pk[14] = 0xd22cbd7baac960fe;
		pk[15] = 0xf8f2125d95a1a5;
		pk[16] = 0x6da774a7f46ef71f;
		pk[17] = 0xfe29e9f440d5a9bb;
		pk[18] = 0x94f64c3de618c741;
		pk[19] = 0x7060cab998c551b8;
		pk[20] = 0x1c46a2192ef5708b;
		pk[21] = 0xca0f795390e2b15e;
		pk[22] = 0x24e444466b79f4dc;
		pk[23] = 0x774df1a4b17262a1;
		pk[24] = 0x83386f5190fa5665;
		pk[25] = 0x6db739ee290e13c0;
		pk[26] = 0x31537fd3d4f2bf21;
		pk[27] = 0xeaf3eee18e65c618;
		pk[28] = 0x4793e4658fb48fce;
		pk[29] = 0xfb28ab516b4788bf;
		pk[30] = 0xaec97a063923178e;
		pk[31] = 0x66dc36bda837b0fb;
		pk[32] = 0xe3f1622a437ed20e;
		pk[33] = 0x3556430071c47271;
		pk[34] = 0xb12e0e6354d3e93c;
		pk[35] = 0xe24eaa67c892383b;
		pk[36] = 0x55b78f45effd77ab;
		pk[37] = 0x11c0109eda55853f;
		pk[38] = 0x8f66f24c94561938;
		pk[39] = 0x2bcd652b4c7be6f9;
		pk[40] = 0xed4caa8351110805;
		pk[41] = 0x61b56483bf564e2b;
		pk[42] = 0x237d95e20b45b26d;
		pk[43] = 0x5fb7296687737f6b;
		pk[44] = 0x19ca0c9c23cf9ac7;
		pk[45] = 0xc090c24065cfaf3e;
		pk[46] = 0x6d9c2476fc854f9;
		pk[47] = 0xe9e1ad88358eb059;
		pk[48] = 0x6b1714b221ac6c5d;
		pk[49] = 0x73de687097ff52d;
		pk[50] = 0xb7e7546cb4df52a3;
		pk[51] = 0x9ecc289180dc490c;
		pk[52] = 0x64834f108c65d1e0;
		pk[53] = 0x1b23955206d101c9;
		pk[54] = 0x49506d1d1043f46a;
		pk[55] = 0x13ccce870a297c2a;
		pk[56] = 0x7712bab83841679a;
		pk[57] = 0x8ca0dfc51d890240;
		pk[58] = 0xc0ba542f5284649e;
		pk[59] = 0xc00c8a55920da147;
		pk[60] = 0xf17e665be1a189f7;
		pk[61] = 0x8015198825f0d652;
		pk[62] = 0xccb736f60a7aaf34;
		pk[63] = 0xfb71e26db415ba2c;
		pk[64] = 0x4b5d165bcaf8c43a;
		pk[65] = 0xd098f1675570c200;
		pk[66] = 0x3614bb9a4016b567;
		pk[67] = 0xf9289e4a56cc024;
		pk[68] = 0xfaa329823edaa5d3;
		pk[69] = 0x883d26c41cd09ff5;
		pk[70] = 0x9916de1743816843;
		pk[71] = 0x1fd31c7c1c9532fc;
		pk[72] = 0x98e524a44216a69b;
		pk[73] = 0xf9bf2123568a9bd;
		pk[74] = 0xa1c258681e776e46;
		pk[75] = 0x2d1b06461d8f36c;
		pk[76] = 0xa7d8fbe3e492ff2a;
		pk[77] = 0xb41211deb76abbe2;
		pk[78] = 0x925e3dd5a0253c55;
		pk[79] = 0x491c08030a3b05;
		pk[80] = 0xe12d019f747e2446;
		pk[81] = 0xb899a3cbe599e667;
		pk[82] = 0xd45b45e7df738ad;
		pk[83] = 0x16c539bf340b2347;
		pk[84] = 0x29041628fd5dba84;
		pk[85] = 0xe5d3fec221ee2371;
		pk[86] = 0xe1d689861f86a7c4;
		pk[87] = 0x9fb8e4d2e7da8af7;
		pk[88] = 0xcac9cb3958c37a92;
		pk[89] = 0x28f06c4e461d5491;
		pk[90] = 0x93d3341ecc6b4876;
		pk[91] = 0x9f21fd92df88cddb;
		pk[92] = 0xf6c9e04a416780bd;
		pk[93] = 0xf6d8c984713382eb;
		pk[94] = 0x7eb3ce26ff0c7d3b;
		pk[95] = 0x67f4f6e1b301efec;
		pk[96] = 0xd2064703da1db79a;
		pk[97] = 0x1192add5aea09bce;
		pk[98] = 0xe7c1b49d2fdda2b9;
		pk[99] = 0x3001f0b60b83a926;
		pk[100] = 0x80d89e8c2bc693fe;
		pk[101] = 0xa97f043325677b0d;
		pk[102] = 0xa3d260ed127ed87e;
		pk[103] = 0xec8800109fdf7c1a;
		pk[104] = 0xe25253f871eaeec6;
		pk[105] = 0x90a2c054361426fd;
		pk[106] = 0x554d70129ccabead;
		pk[107] = 0xddb330edef111091;
		pk[108] = 0xe4e948e9c9fafada;
		pk[109] = 0x4907b3dee45de1ba;
		pk[110] = 0x133d2180387dc1c;
		pk[111] = 0xa893f3a1f287e8fc;
		pk[112] = 0x1a208bf5b64ec573;
		pk[113] = 0xf3de0bad36411ce4;
		pk[114] = 0x92f06e3a68f21d4d;
		pk[115] = 0xf23365726f48f0a;
		pk[116] = 0x1507265337ac07e3;
		pk[117] = 0x57a3a551eb1ec10d;
		pk[118] = 0x3e69cff009cfc8c5;
		pk[119] = 0xc12041f575b038c3;
		pk[120] = 0x3f9e8999c019239f;
		pk[121] = 0x19a537c9ddd85196;
		pk[122] = 0x56903d39181ac454;
		pk[123] = 0x87acde510c501ac8;
		cpa_secret[0] = 0x1209a01020992009;
		cpa_secret[1] = 0x120191200221922;
		cpa_secret[2] = 0x9100c209001a190;
		cpa_secret[3] = 0x101001012920109;
		cpa_secret[4] = 0x992a0ab0120a499;
		cpa_secret[5] = 0x1a221110121a0a02;
		cpa_secret[6] = 0x902191a229000299;
		cpa_secret[7] = 0xa099109920191010;
		cpa_secret[8] = 0x1900319a0b11a19a;
		cpa_secret[9] = 0x92a9a9029199193a;
		cpa_secret[10] = 0x9990000109009902;
		cpa_secret[11] = 0x9a12919100120190;
		cpa_secret[12] = 0x19211199a9111920;
		cpa_secret[13] = 0x9002030019003030;
		cpa_secret[14] = 0x111a290a3922;
		cpa_secret[15] = 0x999a0192091a4929;
		cpa_secret[16] = 0xa21ab990290992aa;
		cpa_secret[17] = 0x1a20c20012309b10;
		cpa_secret[18] = 0x990101999090990;
		cpa_secret[19] = 0x229090b9221a1a10;
		cpa_secret[20] = 0x9a9190a9a09aa1;
		cpa_secret[21] = 0x911991901a01a900;
		cpa_secret[22] = 0x1040a1009a293919;
		cpa_secret[23] = 0x9201393002290b20;
		cpa_secret[24] = 0x210921900109099;
		cpa_secret[25] = 0x22192aa210110910;
		cpa_secret[26] = 0xa9a0209101a00099;
		cpa_secret[27] = 0xa02a0011293090;
		cpa_secret[28] = 0xa211a122020120ab;
		cpa_secret[29] = 0x2013909a0a0a1293;
		cpa_secret[30] = 0x91120a9092902a00;
		cpa_secret[31] = 0xa9ab09b1310a0a91;
		cpa_secret[32] = 0x112010212211a919;
		cpa_secret[33] = 0x21100101191a9019;
		cpa_secret[34] = 0x1900129391aa02;
		cpa_secret[35] = 0xa9309b11039ab191;
		cpa_secret[36] = 0x99031b10020a104b;
		cpa_secret[37] = 0x12b0b190a9911191;
		cpa_secret[38] = 0x9119190919aba90;
		cpa_secret[39] = 0xa31b9929a009b091;
		cpa_secret[40] = 0xa001013a090a10a0;
		cpa_secret[41] = 0xb9aa2929aa099091;
		cpa_secret[42] = 0x109902900099a2;
		cpa_secret[43] = 0x19aa10010b21a0aa;
		cpa_secret[44] = 0x900912a010991991;
		cpa_secret[45] = 0x3b1201111aa0a1b9;
		cpa_secret[46] = 0x9119a012a109201a;
		cpa_secret[47] = 0x321ab0090a12221;
		hash_pk[0] = 0x18581dd9b832a74e;
		hash_pk[1] = 0xd1698f10505e1e80;
		hash_pk[2] = 0x7bae1d2f99bb8d0c;
		hash_pk[3] = 0xfbfda75ddd86d276;
		pseudo_random[0] = 0x897d014b09cbfa0a;
		pseudo_random[1] = 0xead5e4234c09fd2d;
		pseudo_random[2] = 0xdd2d24baff6800ce;
		pseudo_random[3] = 0x295d9604526ba30;
		ct[0] = 0x4d09708f704efec;
		ct[1] = 0xcffae7a845e621db;
		ct[2] = 0xd6bed261011dea1b;
		ct[3] = 0x81829f34c3e93ddd;
		ct[4] = 0x17d0826b906572e0;
		ct[5] = 0x973781da49ce106b;
		ct[6] = 0xf17cd270bb5afcdb;
		ct[7] = 0x8c330f4a0481e49c;
		ct[8] = 0x113075f2ef30b560;
		ct[9] = 0x52a917ddebfd00fb;
		ct[10] = 0x2e2e436a0103f836;
		ct[11] = 0x7aa6b65f1049d91a;
		ct[12] = 0x26b1f1e08178cc15;
		ct[13] = 0xd76e03f0fc16f0ba;
		ct[14] = 0x3f37eb8cc9086a50;
		ct[15] = 0x3b30ad0d6defd618;
		ct[16] = 0xc4c315b72d532b9d;
		ct[17] = 0x44c549dba987876a;
		ct[18] = 0xa40b9fa12f9da025;
		ct[19] = 0x5e8c3c600488a806;
		ct[20] = 0xe9572f3435182af6;
		ct[21] = 0x6e7dda8afef0bcbc;
		ct[22] = 0xd4994644462e94ab;
		ct[23] = 0x744806cee6f92f6d;
		ct[24] = 0x9039dd6e00c35661;
		ct[25] = 0x281cc7510dd72203;
		ct[26] = 0x317c66db401c8525;
		ct[27] = 0x76644201582dcc48;
		ct[28] = 0x5ac9d61fefa2244c;
		ct[29] = 0xa28b837ab395bb74;
		ct[30] = 0xdd6eed1ac0a678e6;
		ct[31] = 0xcc149f17b6f1327f;
		ct[32] = 0x32375a4f29c26f1c;
		ct[33] = 0xd729ad9d0876e725;
		ct[34] = 0x3a0bf079f2362870;
		ct[35] = 0xb4aafa7ad6d7f052;
		ct[36] = 0xd4b7ab695db5bdd3;
		ct[37] = 0xd7d3e5ca85764f0f;
		ct[38] = 0x97ebae3c747073b1;
		ct[39] = 0xd31e87fb79acbf4b;
		ct[40] = 0x3067bd931070471f;
		ct[41] = 0x1c7faea7488fec2;
		ct[42] = 0xc51365be17e0d39b;
		ct[43] = 0x26e9f5bdfe139e46;
		ct[44] = 0x739a2970e99a83b9;
		ct[45] = 0x18a278b374f1e003;
		ct[46] = 0x9568a4bb11ac9f5b;
		ct[47] = 0xaa5e10bb26e353d4;
		ct[48] = 0x9184b5b8fcbd81f2;
		ct[49] = 0xa6175f98d297d575;
		ct[50] = 0x34263ad24bc4f3f3;
		ct[51] = 0xf2ef672952549bb2;
		ct[52] = 0x8524963bf2378618;
		ct[53] = 0x1e62b36a1aad421e;
		ct[54] = 0xfdc0f0608b0a40e5;
		ct[55] = 0x103626780961f898;
		ct[56] = 0xebab4dcb904f5d64;
		ct[57] = 0x8aeef9641e51ba31;
		ct[58] = 0x20ab4bbfa93b735c;
		ct[59] = 0x9acfa51b463948db;
		ct[60] = 0xaaeb65f8cd7c25d4;
		ct[61] = 0xeb649c7abade6896;
		ct[62] = 0xc314f2978cf1513f;
		ct[63] = 0x17301bcb7880ba9e;
		ct[64] = 0xc26e99d5a84cf5ed;
		ct[65] = 0x8515bafe8398dac9;
		ct[66] = 0x94570c1399ed2acc;
		ct[67] = 0x10fc326db8663d63;
		ct[68] = 0x7382e0170c3708c4;
		ct[69] = 0x4d88e61195df2cb;
		ct[70] = 0x4baf846df18ca7c5;
		ct[71] = 0xac6ba2c724e1c162;
		ct[72] = 0xa2d32ae8b7e28501;
		ct[73] = 0x2d7f8f49e23ff7e1;
		ct[74] = 0xb423692eb2a6f968;
		ct[75] = 0x7502a754f8668fe9;
		ct[76] = 0x1a2e0df6749cb915;
		ct[77] = 0x3fe9e9d836a38b1b;
		ct[78] = 0xb6752cb04e982d;
		ct[79] = 0xfb9cd596c1d1fa8b;
		ct[80] = 0xeb0007ab56442b9c;
		ct[81] = 0x5e0c40c5bfcd2e32;
		ct[82] = 0x423c76654bb97e0f;
		ct[83] = 0xf4811eebffd1b602;
		ct[84] = 0x519bea4bb9f14b31;
		ct[85] = 0xdc8e0e146c251fc3;
		ct[86] = 0x48dd122738fc3be8;
		ct[87] = 0x45caea35649312f9;
		ct[88] = 0x1f6772e2deccff29;
		ct[89] = 0xbcae1559210d99c0;
		ct[90] = 0x3e2bf90aa4e1929;
		ct[91] = 0xe756a5bee5c52904;
		ct[92] = 0x7b15d77877e2c0ce;
		ct[93] = 0xf4ca99f4f20e94f7;
		ct[94] = 0xed856b304078656b;
		ct[95] = 0x9107c67120bc5b20;
		ct[96] = 0xc0c321992f695bb0;
		ct[97] = 0xffae5dca61c0b4f5;
		ct[98] = 0xc8e0086b60604112;
		ct[99] = 0x4d47691fd405d18c;
		ct[100] = 0xb1359b1729437c62;
		ct[101] = 0xe4d7e6814b08de48;
		ct[102] = 0x1879765a07c92b04;
		ct[103] = 0x90360ab449ef8ceb;
		ct[104] = 0x950ec7476cf28a4;
		ct[105] = 0xc42f569b198b45ad;
		ct[106] = 0x665eae113bb24ac9;
		ct[107] = 0xf422e7212bfee189;
		ct[108] = 0x4254444fbaa49dbc;
		ct[109] = 0xb97f8d471c1c1430;
		ct[110] = 0xd6bad4c69b75fd89;
		ct[111] = 0x6059550aded55e51;
		ct[112] = 0xc987aecda5507650;
		ct[113] = 0x4570d6f8b2b906ed;
		ct[114] = 0xeca00c66f09f1133;
		ct[115] = 0xc67d9d44f22f0eb3;
		ct[116] = 0xfedc00f892dde0f3;
		ct[117] = 0x8fa94d65c79ff9f3;
		ct[118] = 0x524af6ee5a96a90b;
		ct[119] = 0x89730d29e8846a02;
		ct[120] = 0x1340be615a1cdf73;
		ct[121] = 0x53e20e2131c679fd;
		ct[122] = 0x8f38a9d93bf8d996;
		ct[123] = 0x2528c8ca246bcb30;
		ct[124] = 0x762eb19fb37df3e0;
		ct[125] = 0x23f372e100424bee;
		ct[126] = 0xcb6cfba551b5c88b;
		ct[127] = 0x5c92a93674ff3330;
		ct[128] = 0x1e612321c589e6d5;
		ct[129] = 0x6e4a85bc7b9e1ce6;
		ct[130] = 0x374a22ac955cec6f;
		ct[131] = 0xf03d4af72c0f64dd;
		ct[132] = 0x7c264367beca9b53;
		ct[133] = 0xd021bcbc83f1a1b7;
		ct[134] = 0x99105a7f73fa50e5;
		ct[135] = 0x5300617abe15fe2d;
		*/

		for(i=0; i<124; i++)
			tv[i] = pk[i];

		for(i=0; i<4; i++)
			tv[i+124] = pseudo_random[i];

		for(i=0; i<48; i++)
			tv[i+128] = cpa_secret[i];

		for(i=0; i<136; i++)
			tv[i+200] = ct[i];

		for(i=0; i<4; i++)
			tv[i+340] = hash_pk[i];

		for(i=344; i<1024; i++)
			tv[i] = 0x0000000000000000;
}


uint64_t tiny_hash(uint64_t *p, uint32_t num_words)
{
	uint64_t i, sum=0;
	for(i=0; i<num_words; i++)
		sum = sum + p[i];

	return sum;
}

void send64(uint64_t *p, uint32_t base_address, uint32_t num_words, uint32_t INS_flag)
{
	int i, j;

	uint32_t address_ext = base_address; 	// control[9:0];
	uint32_t wea_ext = 0; 					// control[10];
	uint32_t control_low = 0;
	uint32_t dina_low=0, dina_high=0;
	uint64_t temp;

	printf("Send:num_words = %d\n", num_words);
	for(i=0; i<num_words; i++)
	{
		temp = p[i];
		dina_low = temp & 0xFFFFFFFF;
		temp = temp >> 32;
		dina_high = temp & 0xFFFFFFFF;
		wea_ext = 1;
		address_ext = base_address + i;
		control_low = (INS_flag<<11) + (wea_ext<<10) + address_ext;
		//printf("Send[%d] dina_high = %x dina_low = %x\n", i, dina_high, dina_low);
		axi_address_base[0] = control_low;
		axi_address_base[2] = dina_low; axi_address_base[3] = dina_high;
		for(j=0; j<1000; j++);

		wea_ext = 0;
		control_low = (wea_ext<<10) + address_ext;

		axi_address_base[0] = control_low;
		for(j=0; j<1000; j++);
	}
}

void receive64(uint64_t *p, uint32_t base_address, uint32_t num_words)
{
	int i, j;

	uint32_t address_ext = base_address; 	// control[9:0];
	uint32_t wea_ext = 0; 					// control[10];
	uint32_t control_low = 0;
	uint32_t dina_low=0, dina_high=0;

	printf("Receive:num_words = %d\n", num_words);

	for(i=0; i<num_words; i++)
	{
		address_ext = base_address + i;
		control_low = (wea_ext<<10) + address_ext;

		axi_address_base[0] = control_low;
		dina_low = axi_address_base[4];
		dina_high = axi_address_base[5];

		for(j=0; j<1000; j++);
		//printf("Received[%d] dina_high = %x dina_low = %x\n", i, dina_high, dina_low);
		p[i] = dina_high & 0xFFFFFFFF;
		p[i] = p[i] << 32;
		p[i] = p[i] + dina_low;
	}

}

void exeIns()
{

	// control_low_word (axi_address_base[0]),
	// control_high_word (axi_address_base[1]),
	// dina_ext_low_word (axi_address_base[2]),
	// dina_ext_high_word (axi_address_base[3]),
	// output [31:0] dout_ext_low_word, dout_ext_high_word;
	// output [31:0] status;

	// address_ext = control_low[9:0];
	// wea_ext = control_low[10];
	// rst = control_high[0];
	// start = control_high[1];

	uint32_t control_low = 0, control_high = 0;
	int i;

	// Reset Processor
	control_low = 0; control_high=1;
	axi_address_base[0] = control_low;
	axi_address_base[1] = control_high;

	for(i=0; i<1000; i++);

	printf("Status = %x\n", axi_address_base[6]);

	CYCLE_COUNT = 0;

	// Compute Processor
    //XTime_GetTime(&start);


	control_low = 0; control_high=2;
	axi_address_base[0] = control_low;
	axi_address_base[1] = control_high;

	//for(i=0; i<10000; i++);

	while((axi_address_base[6] & 0x1) == 0)
		printf("Computation done = %x\n", axi_address_base[6]&0x1);


	CYCLE_COUNT = (axi_address_base[6]-1)/2;
	//ARM_CYCLE_COUNT = stop - start;

	printf("Status after executing instructions = %x\n", axi_address_base[6]);
	// Reset Processor
	control_low = 0; control_high=1;
	axi_address_base[0] = control_low;
	axi_address_base[1] = control_high;

	for(i=0; i<1000; i++);

	printf("Status = %x\n", axi_address_base[6]);

	printf("Final Status = %x\n", axi_address_base[6]);
}


int main()
{
	printf("Hello\n");
	int32_t i, j;
	uint64_t a[1024], b[1024];
	uint32_t NUMWORDS;
	uint64_t tv[1024], INS[64];

	int enc_dec_choice=0;
	int proceed=1;

	init_platform();
	axi_address_base   = (uint32_t *) 0x00A0000000;

	// Connections of the registers:
	// control_low_word (axi_address_base[0]),
	// control_high_word (axi_address_base[1]),
	// dina_ext_low_word (axi_address_base[2]),
	// dina_ext_high_word (axi_address_base[3]),
	// output [31:0] dout_ext_low_word, dout_ext_high_word;
	// output [31:0] status;

	printf("Init done \n");

	while(proceed==1){
		for(i=0; i<500; i++)
			j += i;

			printf("Encapsulation/Decapsulation/Keygen [0/1/2]: ");
			scanf("%d", &enc_dec_choice);

			if(enc_dec_choice==0){
				init_INS_enc(INS);
				init_tv_enc(tv);
			}
			else if(enc_dec_choice==1){
				init_INS_dec(INS);
				init_tv_dec(tv);
			}
			else{
				init_INS_keygen(INS);
				init_tv_keygen(tv);
			}
			// Reset output array
			for(i=0; i<1024; i++)
				b[i] = 0;

			send64(INS, 0, 64, 1); // send INS

			// some delay between two send operations
			for(i=0; i<500; i++)
				j += i;

			send64(tv, 0, 1024, 0); // send data

			for(i=0; i<500; i++)
				j += i;

			printf("Executing instruction\n");
			exeIns();
			printf("Executed instruction\n");

			for(i=0; i<500; i++)
				j += i;

			receive64(b, 0, 1024);

			for(i=0; i<1024; i++)
				printf("b[%d] = %llx\n", i, b[i]);

			for(i=0; i<500; i++)
				j += i;


			printf("axi[0]=%x\n", axi_address_base[0]);
			printf("axi[1]=%x\n", axi_address_base[1]);
			printf("axi[2]=%x\n", axi_address_base[2]);
			printf("axi[3]=%x\n", axi_address_base[3]);
			printf("axi[4]=%x\n", axi_address_base[4]);
			printf("axi[5]=%x\n", axi_address_base[5]);
			printf("axi[6]=%x\n", axi_address_base[6]);


			printf("Tinyhash(a) = %llx\n", tiny_hash(a, 1024));
			printf("Tinyhash(b) = %llx\n", tiny_hash(b, 1024));
			printf("CYCLE_COUNT=%d\n", CYCLE_COUNT);
			printf("Proceed [0/1]:");
			scanf("%d", &proceed);
	}

	Xil_DCacheFlush();
	Xil_DCacheDisable();


	printf("Finish\n");

	cleanup_platform();
	return 0;
}
