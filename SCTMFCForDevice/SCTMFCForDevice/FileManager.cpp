#include "stdafx.h"
#include <string.h>
#include "FileManager.h"
#include "Global.h"


//static int zeros = 0;
////�ж��ַ���־λ�Ƿ���ͬ
//bool Check_Ifo(char* pbuf1,char* pbuf2,UINT len)
//{
//	UINT8 i;
//	for(i = 0; i < len; i++) 
//	{
//		if(pbuf1[i]!=pbuf2[i])
//			return false;
//	}//��ͬ
//	return true;//��ͬ
//}
//
////��ȡһ���޷�������
//
//UINT32 Get_num(char* pbuf,UINT len)
//{
//	UINT32 num;
//	if(len == 2) num = (pbuf[1]<<8)|pbuf[0];
//	else if(len == 4) num = (pbuf[3]<<24)|(pbuf[2]<<16)|(pbuf[1]<<8)|pbuf[0];
//	return num;
//}


////-------------------------��WAV�ļ�ͷ-----------------------------------------
//WAVEHEAD ReadWavh(char *pData)
//{
//	//char pData[44];
//	WAVEHEAD Wavh;
//	//FileRead(handle,pData,44);   //���ļ�ͷ
//	//Wavh.wavtype = (string)(pData[0] + pData[1] + pData[2]+ pData[3]);//
//	//strncpy(pData,4);
//	strncpy(Wavh.wavtype,pData,4);
//    Wavh.wavtype[4] = '\0';
//	//Wavh.wavflag = (string)(pData[8] + pData[9] + pData[10] + pData[11]);
//	strncpy(Wavh.wavflag,&pData[8],4);
//	Wavh.wavflag[4] = '\0';
//	//Wavh.dataflag = (string)(pData[36] + pData[37] + pData[38] + pData[39]);
//	strncpy(Wavh.dataflag,&pData[36],4);
//	Wavh.dataflag[4] = '\0';
//	Wavh.datasize = (int)(pData[40] + (pData[41]<<8)+ (pData[42]<<16) + (pData[43]<<24));
//	return Wavh;
//}

int GetData(CString strFileName, double* pData)
{
	CFile myFile(strFileName,CFile::modeRead);
	int dataLength = 0;
	UINT err_flag;
	WAV_FILE wav;
	if(err_flag = WavCheck(&myFile,&wav))
	{
        GetErrMessage(err_flag);
		myFile.Close();
		dataLength = -1;
		return dataLength;
	}
	int len = wav.lSampleDataLen<DATALENGTH?wav.lSampleDataLen:DATALENGTH;   //ȡ���ݳ��ȵ���Сֵ 
	for(int i = 0;i < len; ++i)
	{
        //��ͨ�� �Ͷ�ȡ�����ֽ� ˫ͨ�� �Ͷ�ȡһ���ֽ�
		pData[i] =  double(readInt16(&myFile));
	}

	dataLength = len;
	myFile.Close();
	return dataLength;
}

//-------------------------WAV�ļ�ͷ���----------------------------------------
UINT WavCheck(CFile* pFile,WAV_FILE* pWav)
{
    //pWav->sRIFF_Flag = TEXT("wave");
	//memset(pWav,0,sizeof(WAV_FILE));
	//pWav->sRIFF_Flag = TEXT("wave");
	pWav->sRIFF_Flag = readString(pFile);
	if(pWav->sRIFF_Flag.Compare(TEXT("RIFF")))
	//if(!Check_Ifo(pbuf,"RIFF"))
		return RIFF_ERR;//RIFF��־����
	pWav->lWavlen = readLong32(pFile);//�ļ����ȣ�����ƫ��4byte
	pWav->sWAVE_Flag = readString(pFile);
	if(pWav->sWAVE_Flag.Compare(TEXT("WAVE")))  
		return WAVE_ERR;//WAVE��־����
	pWav->sFMT_Flag = readString(pFile);
	if(pWav->sFMT_Flag.Compare(TEXT("fmt ")))
	//if(Check_Ifo(pbuf+12,"fmt "))
		return FMT_ERR;//fmt��־����
	pWav->lAdditionalInfo = readLong32(pFile);
	pWav->iFormart = readInt16(pFile);
	//wav1.formart = Get_num(pbuf+20,2);//��ʽ���
	pWav->iChannelsNum = readInt16(pFile);
	pWav->lSampleRate = readLong32(pFile);
	pWav->lByterate = readLong32(pFile);
	pWav->iBlockalign = readInt16(pFile);
	pWav->iSampleBits = readInt16(pFile);
	pWav->sDATA_FLAG = readString(pFile);
	if(pWav->sDATA_FLAG.Compare(TEXT("data")))
         return DATA_ERR;//data��־����
	pWav->lDataLen = readLong32(pFile);
	pWav->lSampleDataLen = pWav->lDataLen/(pWav->iSampleBits/8)/pWav->iChannelsNum; 
	//wav1.CHnum = Get_num(pbuf+22,2);//ͨ����

	//wav1.SampleRate = Get_num(pbuf+24);//������
	//wav1.speed = Get_num(pbuf+28);//��Ƶ��������
	//wav1.ajust = Get_num(pbuf+32,2);//���ݿ������
	//wav1.SampleBits = Get_num(pbuf+34,2);//��������λ��
	////Bitnum = wav1.SampleBits;
	//if(Check_Ifo(pbuf+36,"data")) return DATA_ERR;//data��־����
	//wav1.DATAlen=Get_num(pbuf+40,4); //���ݳ���	

	//typedef struct 
	//{
	//	CString    sRIFF_Flag;   ////RIFF��־
	//	long       lWavlen;      //�ļ����ȣ�����ƫ��4byte
	//	CString    sWAVE_Flag;    //WAVE��־
	//	CString    sFMT_Flag;    //fmt��־
	//	long       lAdditionalInfo;  //������Ϣ
	//	int        iFormart;     //��ʽ���  ���뷽ʽ1��PCM 
	//	int        iChannelsNum;       //ͨ���� 1����ͨ�� 2��˫ͨ��
	//	long       lSampleRate;   //������
	//	long       lByterate;        //��Ƶ�������� ÿ�������ֽ���
	//	int        iBlockalign;        //���ݿ������
	//	int        iSampleBits;   //��������λ��
	//	CString    sDATA_FLAG;    //data��־
	//	long       lDataLen;      //data���ݳ���	
	//	long       lSampleDataLen;  //�������ݳ���
	//}WAV_FILE;

  //  CString str;
  //  str.Format(TEXT("�ļ����ȣ�%u��������Ϣ��%u����ʽ���%u��ͨ������%u�������ʣ�%u����Ƶ�������ʣ�%u�����ݿ��������%u����������λ����%u��data���ݳ��ȣ�%u,ʵ�����ݳ��ȣ�%u��"),
		//pWav->lWavlen,
		//pWav->lAdditionalInfo,
		//pWav->iFormart,
		//pWav->iChannelsNum,
		//pWav->lSampleRate,
		//pWav->lByterate,
		//pWav->iBlockalign,
		//pWav->iSampleBits,
		//pWav->lDataLen,
		//pWav->lSampleDataLen);
  //  MessageBox(NULL,str,TEXT("����"),MB_OK);
    
	return SUCCESS;
}  

void  GetErrMessage(UINT flag)
{
	switch(flag){
		case RIFF_ERR:
			{
				MessageBox(NULL,TEXT("WAVE�ļ�RIFF��־����"),TEXT("����"),MB_OK);
				break;
			}
		case WAVE_ERR:
			{
				MessageBox(NULL,TEXT("WAVE�ļ�WAVE��־����"),TEXT("����"),MB_OK);
				break;
			}
		case FMT_ERR:
			{
				MessageBox(NULL,TEXT("WAVE�ļ�FMT��־����"),TEXT("����"),MB_OK);
				break;
			}
		case DATA_ERR:
			{
				MessageBox(NULL,TEXT("WAVE�ļ�DATA��־����"),TEXT("����"),MB_OK);
				break;
			}
		default:
			break;
	}
}


CString readString(CFile* pFile,int len){
	byte* buf = new byte[len];
	int iRealLen = pFile->Read(buf,len);
	if(iRealLen == 0)
	{
		delete []buf;
		return TEXT("");
	}
	CString s(buf);
	delete []buf;
	buf = NULL;
	return s;
}

int readInt16(CFile* pFile) {
	signed char buf[2] = {0};   //�޷�����
	int res = 0;
	int iRealLen = pFile->Read(buf,2);
	if(iRealLen == 0)
	{
		//zeros++;
		return res;
	}
	res = (buf[0] & 0x000000FF) | (((int) buf[1]) << 8);
	return res;
}

//int readSignedInt16(CFile* pFile) {
//	signed char buf[2] = {0};   //�з�����
//	int res = 0;
//	int iRealLen = pFile->Read(buf,2);
//	if(iRealLen == 0)
//	{
//		//zeros++;
//		return res;
//	}
//	res = buf[0] | ( buf[1] << 8);
//	return res;
//}

int readInt8(CFile* pFile) {
	int buf = 0;
	int res = 0;
	int iRealLen = pFile->Read(&buf,1);
	if(iRealLen == 0)
	{
		return res;
	}
	res = buf;
	return res;
}

long readLong32(CFile* pFile) {
	long res = 0;
	unsigned char b[4] = {0};
	int iRealLen = pFile->Read(b,4);
	if(iRealLen == 0)
	{
		return res;
	}
	//res = (buf[0] & 0x000000FF) | (((int) (buf[1] & 0x000000FF)) << 8);
	res = b[0] | ((b[1]& 0x000000FF) << 8) | ((b[2]& 0x000000FF) << 16) | ((b[3]& 0x000000FF) << 24);
	return res;
}