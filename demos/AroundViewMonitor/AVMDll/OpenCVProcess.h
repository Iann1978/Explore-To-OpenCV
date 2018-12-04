#pragma once
class OpenCVProcess
{
public:
	static int intValues[32];
public:
	virtual void Process(Mat** inputs, Mat** outputs);

};

