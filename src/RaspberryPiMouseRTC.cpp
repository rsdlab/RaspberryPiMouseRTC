// -*- C++ -*-
/*!
 * @file  RaspberryPiMouseRTC.cpp
 * @brief RaspberryPiMouseRTC
 * @date $Date$
 *
 * $Id$
 */


#define _USE_MATH_DEFINES
#include <math.h>
#include "RaspberryPiMouseRTC.h"

// Module specification
// <rtc-template block="module_spec">
static const char* raspberrypimousertc_spec[] =
{
	"implementation_id", "RaspberryPiMouseRTC",
	"type_name",         "RaspberryPiMouseRTC",
	"description",       "RaspberryPiMouseRTC",
	"version",           "1.0.0",
	"vendor",            "Meijo Univ.",
	"category",          "MobileRobot",
	"activity_type",     "PERIODIC",
	"kind",              "DataFlowComponent",
	"max_instance",      "1",
	"language",          "C++",
	"lang_type",         "compile",
	// Configuration variables
	"conf.default.max_velocity", "0.2",
	"conf.default.max_acceleration", "0.52",
	"conf.default.max_tangential_velocity", "0.52",
	"conf.default.max_tangential_acceleration", "0.314",
	"conf.default.distance_of_wheels", "0.095",
	"conf.default.diameter_of_wheel", "0.048",
	"conf.default.step_angle", "0.9",
	// Widget
	"conf.__widget__.max_velocity", "text",
	"conf.__widget__.max_acceleration", "text",
	"conf.__widget__.max_tangential_velocity", "text",
	"conf.__widget__.max_tangential_acceleration", "text",
	"conf.__widget__.distance_of_wheels", "text",
	"conf.__widget__.diameter_of_wheel", "text",
	"conf.__widget__.step_angle", "text",
	// Constraints
	""
};
// </rtc-template>

static RPMD::RaspberryPiMouseDevice rpmd;

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RaspberryPiMouseRTC::RaspberryPiMouseRTC(RTC::Manager* manager)
	// <rtc-template block="initializer">
	: RTC::DataFlowComponentBase(manager),
	m_target_velocity_inIn("target_velocity_in", m_target_velocity_in),
	m_pose_update_inIn("pose_update_in", m_pose_update_in),
	m_buzzer_hz_inIn("buzzer_hz_in", m_buzzer_hz_in),
	m_led4bit_inIn("led4bit_in", m_led4bit_in),
	m_current_velocity_outOut("current_velocity_out", m_current_velocity_out),
	m_current_pose_outOut("current_pose_out", m_current_pose_out),
	m_ir_sensor_outOut("ir_sensor_out", m_ir_sensor_out),
	m_switch3bit_outOut("switch3bit_out", m_switch3bit_out)

	  // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RaspberryPiMouseRTC::~RaspberryPiMouseRTC()
{
}



RTC::ReturnCode_t RaspberryPiMouseRTC::onInitialize()
{
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers
	addInPort("target_velocity_in", m_target_velocity_inIn);
	addInPort("pose_update_in", m_pose_update_inIn);
	addInPort("buzzer_hz_in", m_buzzer_hz_inIn);
	addInPort("led4bit_in", m_led4bit_inIn);

	// Set OutPort buffer
	addOutPort("current_velocity_out", m_current_velocity_outOut);
	addOutPort("current_pose_out", m_current_pose_outOut);
	addOutPort("ir_sensor_out", m_ir_sensor_outOut);
	addOutPort("switch3bit_out", m_switch3bit_outOut);

	// Set service provider to Ports

	// Set service consumers to Ports

	// Set CORBA Service Ports

	// </rtc-template>

	// <rtc-template block="bind_config">
	// Bind variables and configuration variable
	bindParameter("max_velocity", m_max_velocity, "0.2");
	bindParameter("max_acceleration", m_max_acceleration, "0.52");
	bindParameter("max_tangential_velocity", m_max_tangential_velocity, "0.52");
	bindParameter("max_tangential_acceleration", m_max_tangential_acceleration, "0.314");
	bindParameter("distance_of_wheels", m_distance_of_wheels, "0.095");
	bindParameter("diameter_of_wheel", m_diameter_of_wheel, "0.048");
	bindParameter("step_angle", m_step_angle, "0.9");
	// </rtc-template>

	return RTC::RTC_OK;
}

/*
   RTC::ReturnCode_t RaspberryPiMouseRTC::onFinalize()
   {
   return RTC::RTC_OK;
   }
   */

/*
   RTC::ReturnCode_t RaspberryPiMouseRTC::onStartup(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
   */

/*
   RTC::ReturnCode_t RaspberryPiMouseRTC::onShutdown(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
   */


RTC::ReturnCode_t RaspberryPiMouseRTC::onActivated(RTC::UniqueId ec_id)
{
	m_ir_sensor_out.data.length(RPMD::nIR);
	for(size_t i = 0; i < static_cast< size_t >(RPMD::nIR); ++i)
	{
		m_ir_sensor_out.data[i] = 0;
	}

	m_switch3bit_out.data.length(RPMD::nSW);
	for(size_t i = 0; i < static_cast< size_t >(RPMD::nSW); ++i)
	{
		m_switch3bit_out.data[i] = false;
	}

	double step_angle_radian = m_step_angle*M_PI/180;
	

	m_current_velocity_out.data.vx = 0.0;
	m_current_velocity_out.data.vy = 0.0;
	m_current_velocity_out.data.va = 0.0;

	m_current_pose_out.data.position.x = 0.0;
	m_current_pose_out.data.position.y = 0.0;
	m_current_pose_out.data.heading = 0.0;

	rpmd.setBodyParameter(m_distance_of_wheels, m_diameter_of_wheel, 
			step_angle_radian);

	rpmd.setMaxFrequency(m_max_velocity / (m_diameter_of_wheel / 2.0)
			/ step_angle_radian);
	rpmd.setAcceleration(m_max_acceleration / (m_diameter_of_wheel / 2.0)
			/ step_angle_radian);

	rpmd.servoON();

	return RTC::RTC_OK;
}


RTC::ReturnCode_t RaspberryPiMouseRTC::onDeactivated(RTC::UniqueId ec_id)
{
	rpmd.servoOFF();
	return RTC::RTC_OK;
}


RTC::ReturnCode_t RaspberryPiMouseRTC::onExecute(RTC::UniqueId ec_id)
{
	if(m_target_velocity_inIn.isNew())
	{
		m_target_velocity_inIn.read();

		//std::cout << "vx: " << m_target_velocity_in.data.vx << std::endl;
		//std::cout << "vy: " << m_target_velocity_in.data.vy << std::endl;
		//std::cout << "va: " << m_target_velocity_in.data.va << std::endl;

		rpmd.setTargetVelocity(m_target_velocity_in.data.vx, 
				m_target_velocity_in.data.va);

/*
		double vL = m_target_velocity_in.data.vx - 
			20.0 * m_target_velocity_in.data.va * m_distance_of_wheels / 2.0;
		double vR = m_target_velocity_in.data.vx +
			20.0 * m_target_velocity_in.data.va * m_distance_of_wheels / 2.0;
*/
/*
		double v = sqrt(pow(m_target_velocity_in.data.vx, 2.0) +
				pow(m_target_velocity_in.data.vy, 2.0));
		double vL = v - m_distance_of_wheels * 
				m_target_velocity_in.data.va / 2.0;
		double vR = v + m_distance_of_wheels * 
				m_target_velocity_in.data.va / 2.0;
*/
/*
		rpmd.setVelocity(RPMD::LEFT,
				vL / (m_diameter_of_wheel / 2.0) / step_angle_radian);
		rpmd.setVelocity(RPMD::RIGHT,
				vR / (m_diameter_of_wheel / 2.0) / step_angle_radian);
*/
	}

	if(m_pose_update_inIn.isNew())
	{
		m_pose_update_inIn.read();
		rpmd.setCurrentPose(m_pose_update_in.data.position.x, 
				m_pose_update_in.data.position.y, m_pose_update_in.data.heading);
	}

	if(m_led4bit_inIn.isNew())
	{
		m_led4bit_inIn.read();
		//std::cout << "get led command" << std::endl;

		for(size_t i = 0; i < static_cast< size_t >(RPMD::nLED); ++i)
		{
			//std::cout << (m_led4bit_in.data[i] ? "ON " : "OFF ");
			rpmd.setLED(static_cast< RPMD::LED_e >(i), m_led4bit_in.data[i]);
		}
		//std::cout << std::endl;
	}

	if(m_buzzer_hz_inIn.isNew())
	{
		m_buzzer_hz_inIn.read();
		//std::cout << "get buzzer command" << std::endl;

		rpmd.setBUZZER(m_buzzer_hz_in.data);
	}

	rpmd.proc();

/*
	double current_vL = rpmd.getCurrentVelocity(RPMD::LEFT)
		* step_angle_radian * m_diameter_of_wheel / 2.0;
	double current_vR = rpmd.getCurrentVelocity(RPMD::RIGHT)
		* step_angle_radian * m_diameter_of_wheel / 2.0;
	m_current_velocity.data.vx = (current_vL + current_vR) / 2.0;
	m_current_velocity.data.va = (current_vR - current_vL)
		* m_distance_of_wheels / 2.0;
*/

	m_current_velocity_out.data.vx = rpmd.getCurrentForwardVelocity();
	m_current_velocity_out.data.va = rpmd.getCurrentTangentialVelocity();
	m_current_pose_out.data.position.x = rpmd.getCurrentPoseX();
	m_current_pose_out.data.position.y = rpmd.getCurrentPoseY();
	m_current_pose_out.data.heading = rpmd.getCurrentPoseW();

	m_current_velocity_outOut.write();
	m_current_pose_outOut.write();

	bool switch_trig = false;
	for(size_t i = 0; i < static_cast< size_t >(RPMD::nSW); ++i)
	{
		bool p = rpmd.switchOf(static_cast< RPMD::SW_e >(i));
		if(p != m_switch3bit_out.data[i])
		{
			m_switch3bit_out.data[i] = p;
			switch_trig = true;
		}
	}
	if(switch_trig)
	{
		m_switch3bit_outOut.write();
	}

	for(size_t i = 0; i < static_cast< size_t >(RPMD::nIR); ++i)
	{
		m_ir_sensor_out.data[i] = rpmd.irSensor(static_cast< RPMD::IR_e >(i));
	}
	m_ir_sensor_outOut.write();

	return RTC::RTC_OK;
}

/*
   RTC::ReturnCode_t RaspberryPiMouseRTC::onAborting(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
   */

/*
   RTC::ReturnCode_t RaspberryPiMouseRTC::onError(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
   */

/*
   RTC::ReturnCode_t RaspberryPiMouseRTC::onReset(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
   */

/*
   RTC::ReturnCode_t RaspberryPiMouseRTC::onStateUpdate(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
   */

/*
   RTC::ReturnCode_t RaspberryPiMouseRTC::onRateChanged(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
   */



extern "C"
{

	void RaspberryPiMouseRTCInit(RTC::Manager* manager)
	{
		coil::Properties profile(raspberrypimousertc_spec);
		manager->registerFactory(profile,
				RTC::Create<RaspberryPiMouseRTC>,
				RTC::Delete<RaspberryPiMouseRTC>);
	}

};


