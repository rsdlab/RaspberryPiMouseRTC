///////////////////////////////////////////////////////////////////////
//Raspberry Pi Mouse Device Class
//このクラスはRaspberry Pi Mouse用のデバイスアクセスクラスです．
//Written  by Motoharu Fujihara   Kawakami, Meijo Univ.
//Modified by Kenichi Ohara   , Meijo Univ.
//=====================================================================
//Version Information
//バージョン管理
//=====================================================================
//Ver. 0.1:	Basic Implementation 	2015/12/01
//                基本実装
//=====================================================================
//Dependency
//依存性
//=====================================================================
//To use the class, following driver should be installed
//このクラスを使うためには，下記のドライバをインストールしておく必要があります．
//
//https://github.com/rt-net/RaspberryPiMouse
///////////////////////////////////////////////////////////////////////
#include "RaspberryPiMouseDevice.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

namespace RPMD
{
	RaspberryPiMouseDevice::RaspberryPiMouseDevice()
		: wheels_distance(0.0), wheel_dir(0.0), step_angle(0.0), max_frequency(), acceleration(), current_frequency(), 
		target_frequency(), current_x(0.0), current_y(0.0), current_w(0.0), 
		prev_clock(), current_clock(), moteren("/dev/rtmotoren0"), 
		buzzer("/dev/rtbuzzer0"), motor(), led(), push_switch(), 
		irsensor("/dev/rtlightsensor0")
	{
		motor[LEFT] = std::string("/dev/rtmotor_raw_l0");
		motor[RIGHT] = std::string("/dev/rtmotor_raw_r0");

		for(size_t i = 0; i < static_cast< size_t >(nLED); ++i)
		{
			std::stringstream ss;
			ss << "/dev/rtled" << i;
			led[i] = ss.str();
		}

		for(size_t i = 0; i < static_cast< size_t >(nSW); ++i)
		{
			std::stringstream ss;
			ss << "/dev/rtswitch" << i;
			push_switch[i] = ss.str();
		}

		//prev_clock = clock();
		//current_clock = clock();

		gettimeofday(&prev_clock, NULL);
		gettimeofday(&current_clock, NULL);
	}

	RaspberryPiMouseDevice::~RaspberryPiMouseDevice()
	{
	}

	void RaspberryPiMouseDevice::servoON()
	{
		std::ofstream ofs(moteren.c_str());
		ofs << 1;
		ofs.close();
	}

	void RaspberryPiMouseDevice::servoOFF()
	{
		std::ofstream lmofs(motor[LEFT].c_str());
		std::ofstream rmofs(motor[RIGHT].c_str());
		lmofs << 0;
		rmofs << 0;
		rmofs.close();
		lmofs.close();
		std::ofstream ofs(moteren.c_str());
		ofs << 0;
		ofs.close();
	}

	void RaspberryPiMouseDevice::setBodyParameter(double _dis, 
			double _dir, double _angle)
	{
		wheels_distance = _dis;
		wheel_dir = _dir;
		step_angle = _angle;
	}

	void RaspberryPiMouseDevice::setMaxFrequency(double _max_frequency)
	{
		max_frequency = _max_frequency;
	}

	void RaspberryPiMouseDevice::setAcceleration(double _acceleration)
	{
		acceleration = _acceleration / (wheel_dir / 2.0) / step_angle;
	}
	
	double RaspberryPiMouseDevice::getCurrentForwardVelocity()
	{
		return (current_frequency[LEFT] + current_frequency[RIGHT]) 
			/ 2.0 * step_angle * (wheel_dir / 2.0);
	}

	double RaspberryPiMouseDevice::getCurrentTangentialVelocity()
	{
		return ((current_frequency[RIGHT] - current_frequency[LEFT])
			/ (wheels_distance / 2.0)) / 2.0 * step_angle * (wheel_dir / 2.0);
	}

	void RaspberryPiMouseDevice::setTargetVelocity(double _v_forward, 
			double _v_rotation)
	{
		int frequency[nSTM];
		double _v[nSTM];
		
		_v[LEFT] = _v_forward - _v_rotation * wheels_distance / 2.0; 
		_v[RIGHT] = _v_forward + _v_rotation * wheels_distance / 2.0;
		
		
		for(size_t i = 0; i < nSTM; ++i)
		{
			
			frequency[i] = _v[i] / (wheel_dir / 2.0) / step_angle;
			//std::cout << frequency[i] << "\t" << max_frequency << std::endl;
			if(frequency[i] > max_frequency)
			{
				frequency[i] = max_frequency;
			}
			else if(frequency[i] < -1 * max_frequency)
			{
				frequency[i] = -1 * max_frequency;
			}

			//std::cout << "motor_target: " << static_cast< int >(i)
			//	<< " frequency: " << frequency[i] << std::endl;
			target_frequency[i] = frequency[i];
		}
	}

	double RaspberryPiMouseDevice::getCurrentPoseX()
	{
		return current_x;
	}

	double RaspberryPiMouseDevice::getCurrentPoseY()
	{
		return current_y;
	}

	double RaspberryPiMouseDevice::getCurrentPoseW()
	{
		return current_w;
	}

	void RaspberryPiMouseDevice::setCurrentPose(double _x, double _y, 
			double _w)
	{
		current_x = _x;
		current_y = _y;
		current_w = _w;
	}

	void RaspberryPiMouseDevice::setLED(LED_e target, bool b)
	{
		std::ofstream ofs(led[target].c_str());
		ofs << (b ? 1 : 0);
		ofs.close();
	}

	void RaspberryPiMouseDevice::setBUZZER(int hz)
	{
		std::ofstream ofs(buzzer.c_str());
		ofs << hz;
		ofs.close();
	}

	bool RaspberryPiMouseDevice::switchOf(SW_e target)
	{
		int ret;

		std::ifstream ifs(push_switch[target].c_str());
		ifs >> ret;
		ifs.close();

		return (ret != 0) ? true : false;
	}

	int RaspberryPiMouseDevice::irSensor(IR_e target)
	{
		std::vector< int > rets(nIR);
		std::ifstream ifs(irsensor.c_str());
		ifs >> rets[0] >> rets[1] >> rets[2] >> rets[3];
		ifs.close();
		return rets[target];
	}

	void RaspberryPiMouseDevice::proc()
	{
		//current_clock = clock();
		gettimeofday(&current_clock, NULL);
		double diff_time = (current_clock.tv_sec - prev_clock.tv_sec) + (current_clock.tv_usec - prev_clock.tv_usec) * 1.0E-6;
		
		static double ctime = 0;
		ctime += diff_time;
		//std::cout << ctime << std::endl;
		if(diff_time <= 0.0){gettimeofday(&prev_clock, NULL); return;}
		if(diff_time > 0.5){gettimeofday(&prev_clock, NULL); return;}

		//std::cout << current_frequency[LEFT] << std::endl;

		double v_forward = 
			(current_frequency[LEFT] + current_frequency[RIGHT]) / 2.0 * (wheel_dir / 2.0) * step_angle; 
		current_x += v_forward * cos(current_w) * diff_time;
		current_y += v_forward * sin(current_w) * diff_time;
		current_w += static_cast< double >(current_frequency[RIGHT] - 
				current_frequency[LEFT]) / 2.0 * (wheel_dir / 2.0) * step_angle / (wheels_distance / 2.0) * 
				diff_time;
		//std::cout << current_x << "\t" << current_y << "\t" << current_w << std::endl;
		//std::cout << v_forward << "\t" << diff_time << std::endl;
		


		double allowed_acc = acceleration * diff_time; 
		for(size_t i = 0; i < nSTM; ++i)
		{
			if(current_frequency[i] != target_frequency[i])
			{
				if(abs(current_frequency[i] - target_frequency[i])
						< allowed_acc)
				{
					current_frequency[i] = target_frequency[i];
				}
				else if(current_frequency[i] < target_frequency[i])
				{
					current_frequency[i] += allowed_acc;
				}
				else
				{
					current_frequency[i] -= allowed_acc;
				}

				sendFrequency(static_cast< STM_e >(i), current_frequency[i]);
			}
		}

		gettimeofday(&prev_clock, NULL);
	}

	void RaspberryPiMouseDevice::sendFrequency(STM_e target, int value)
	{
		std::ofstream ofs(motor[target].c_str());
		ofs << value;
		ofs.close();
	}
}

