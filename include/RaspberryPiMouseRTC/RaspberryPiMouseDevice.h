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
#include <string>
#include <time.h>

namespace RPMD
{
	enum STM_e
	{
		LEFT, RIGHT,
		nSTM
	};
	enum LED_e
	{
		LONE, LTWO, LTHREE, LFOUR,
		nLED
	};
	enum SW_e
	{
		SONE, STWO, STHREE,
		nSW
	};
	enum IR_e
	{
		RIGHT_FRONT, RIGHT_SIDE, LEFT_SIDE, LEFT_FRONT,
		nIR
	};

	class RaspberryPiMouseDevice
	{
		public:
			RaspberryPiMouseDevice();
			~RaspberryPiMouseDevice();
			void servoON();
			void servoOFF();

			void setBodyParameter(double, double, double);
			void setMaxFrequency(double);
			void setAcceleration(double);

			double getCurrentForwardVelocity();
			double getCurrentTangentialVelocity();
			void setTargetVelocity(double, double); 
			double getCurrentPoseX();
			double getCurrentPoseY();
			double getCurrentPoseW();
			void setCurrentPose(double, double, double);

			void setLED(LED_e, bool); 
			void setBUZZER(int);
			bool switchOf(SW_e);
			int irSensor(IR_e);

			void proc();

		private:
			void sendFrequency(STM_e, int);

			double wheels_distance;
			double wheel_dir;
			double step_angle;

			int max_frequency;
			int acceleration;

			int current_frequency[nSTM];
			int target_frequency[nSTM];

			double current_x;
			double current_y;
			double current_w;

			clock_t prev_clock;
			clock_t current_clock;

			std::string moteren;
			std::string buzzer;
			std::string motor[nSTM];
			std::string led[nLED];
			std::string push_switch[nSW];
			std::string irsensor;
	};
}

