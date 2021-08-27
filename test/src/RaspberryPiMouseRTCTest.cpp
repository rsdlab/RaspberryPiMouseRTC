// -*- C++ -*-
/*!
 * @file  RaspberryPiMouseRTCTest.cpp
 * @brief RaspberryPiMouseRTC
 * @date $Date$
 *
 * $Id$
 */

#include "RaspberryPiMouseRTCTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* raspberrypimousertc_spec[] =
  {
    "implementation_id", "RaspberryPiMouseRTCTest",
    "type_name",         "RaspberryPiMouseRTCTest",
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
    "conf.default.step_angle", "1.8",

    // Widget
    "conf.__widget__.max_velocity", "text",
    "conf.__widget__.max_acceleration", "text",
    "conf.__widget__.max_tangential_velocity", "text",
    "conf.__widget__.max_tangential_acceleration", "text",
    "conf.__widget__.distance_of_wheels", "text",
    "conf.__widget__.diameter_of_wheel", "text",
    "conf.__widget__.step_angle", "text",
    // Constraints

    "conf.__type__.max_velocity", "double",
    "conf.__type__.max_acceleration", "double",
    "conf.__type__.max_tangential_velocity", "double",
    "conf.__type__.max_tangential_acceleration", "double",
    "conf.__type__.distance_of_wheels", "double",
    "conf.__type__.diameter_of_wheel", "double",
    "conf.__type__.step_angle", "double",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RaspberryPiMouseRTCTest::RaspberryPiMouseRTCTest(RTC::Manager* manager)
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
RaspberryPiMouseRTCTest::~RaspberryPiMouseRTCTest()
{
}



RTC::ReturnCode_t RaspberryPiMouseRTCTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("current_velocity_out", m_current_velocity_outIn);
  addInPort("current_pose_out", m_current_pose_outIn);
  addInPort("ir_sensor_out", m_ir_sensor_outIn);
  addInPort("switch3bit_out", m_switch3bit_outIn);

  // Set OutPort buffer
  addOutPort("target_velocity_in", m_target_velocity_inOut);
  addOutPort("pose_update_in", m_pose_update_inOut);
  addOutPort("buzzer_hz_in", m_buzzer_hz_inOut);
  addOutPort("led4bit_in", m_led4bit_inOut);

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
  bindParameter("step_angle", m_step_angle, "1.8");
  // </rtc-template>

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RaspberryPiMouseRTCTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RaspberryPiMouseRTCTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RaspberryPiMouseRTCTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RaspberryPiMouseRTCTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RaspberryPiMouseRTCTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t RaspberryPiMouseRTCTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RaspberryPiMouseRTCTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RaspberryPiMouseRTCTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RaspberryPiMouseRTCTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RaspberryPiMouseRTCTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RaspberryPiMouseRTCTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{

  void RaspberryPiMouseRTCTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(raspberrypimousertc_spec);
    manager->registerFactory(profile,
                             RTC::Create<RaspberryPiMouseRTCTest>,
                             RTC::Delete<RaspberryPiMouseRTCTest>);
  }

};


