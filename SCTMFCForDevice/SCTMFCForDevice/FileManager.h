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
//	UCHAR    chRIFF[4];   ////RIFF��־
//	UINT32   wavlen;      //�ļ����ȣ�����ƫ��4byte
//	UCHAR    chWAV[4];    //WAVE��־
//	UCHAR    chFMT[4];    //fmt��־
//	UINT16   formart;     //��ʽ���
//	UINT16   CHnum;       //ͨ����
//	UINT32   SampleRate;   //������
//	UINT32   speed;        //��Ƶ��������
//	UINT16   ajust;        //���ݿ������
//	UINT16   SampleBits;   //��������λ��
//	UCHAR    chDATA[4];    //data��־
//	UINT32   DATAlen;      //���ݳ���	
//}WAV_file;

typedef struct 
{
	CString    sRIFF_Flag;   ////RIFF��־
	long       lWavlen;      //�ļ����ȣ�����ƫ��4byte
	CString    sWAVE_Flag;    //WAVE��־
	CString    sFMT_Flag;    //fmt��־
	long       lAdditionalInfo;  //������Ϣ
	int        iFormart;     //��ʽ���  ���뷽ʽ1��PCM 
	int        iChannelsNum;       //ͨ���� 1����ͨ�� 2��˫ͨ��
	long       lSampleRate;   //������
	long       lByterate;        //��Ƶ�������� ÿ�������ֽ���
	int        iBlockalign;        //���ݿ������
	int        iSampleBits;   //��������λ��
	CString    sDATA_FLAG;    //data��־
	long       lDataLen;      //data���ݳ���	
	long       lSampleDataLen;  //�������ݳ���
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