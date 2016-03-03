#ifndef __SCT__FILEMANABER_sdg2h_3sweysd_454sfd_HHH
#define __SCT__FILEMANABER_sdg2h_3sweysd_454sfd_HHH
//

#define  HEADERLENGTH        44
#define  SUCCESS              0
#define  RIFF_ERR             1
#define  WAVE_ERR             2
#define  FMT_ERR              3
#define  DATA_ERR             4


//typedef struct 
//{
//	UCHAR    chRIFF[4];   ////RIFF标志
//	UINT32   wavlen;      //文件长度，数据偏移4byte
//	UCHAR    chWAV[4];    //WAVE标志
//	UCHAR    chFMT[4];    //fmt标志
//	UINT16   formart;     //格式类别
//	UINT16   CHnum;       //通道数
//	UINT32   SampleRate;   //采样率
//	UINT32   speed;        //音频传送速率
//	UINT16   ajust;        //数据块调速数
//	UINT16   SampleBits;   //样本数据位数
//	UCHAR    chDATA[4];    //data标志
//	UINT32   DATAlen;      //数据长度	
//}WAV_file;

typedef struct 
{
	CString    sRIFF_Flag;   ////RIFF标志
	long       lWavlen;      //文件长度，数据偏移4byte
	CString    sWAVE_Flag;    //WAVE标志
	CString    sFMT_Flag;    //fmt标志
	long       lAdditionalInfo;  //附加信息
	int        iFormart;     //格式类别  编码方式1：PCM 
	int        iChannelsNum;       //通道数 1：单通道 2：双通道
	long       lSampleRate;   //采样率
	long       lByterate;        //音频传送速率 每秒所需字节数
	int        iBlockalign;        //数据块调速数
	int        iSampleBits;   //样本数据位数
	CString    sDATA_FLAG;    //data标志
	long       lDataLen;      //data数据长度	
	long       lSampleDataLen;  //采样数据长度
}WAV_FILE;



//WAVEHEAD ReadWavh(char *pdata);
int GetData(CString strFileName,double* pData);
//UINT32 Get_num(char* pbuf,UINT len = 4);
//bool Check_Ifo(char* pbuf1,char* pbuf2,UINT len = 4);
UINT WavCheck(CFile* pFile,WAV_FILE* pWav);
void  GetErrMessage(UINT flag);

CString readString(CFile* pFile,int len = 4);

//int readSignedInt16(CFile* pFile);
int readInt16(CFile* pFile);
int readInt8(CFile* pFile);
long readLong32(CFile* pFile);






#endif