// -*- C++ -*-
/*!
 * @file  RaspberryPiMouseRTCTest.h
 * @brief RaspberryPiMouseRTC
 * @date  $Date$
 *
 * $Id$
 */

#ifndef RASPBERRYPIMOUSERTC_TEST__H
#define RASPBERRYPIMOUSERTC_TEST_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">
#include "ExtendedDataTypesSVC_impl.h"
#include "BasicDataTypeSVC_impl.h"

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="port_stub_h">
// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

/*!
 * @class RaspberryPiMouseRTCTest
 * @brief RaspberryPiMouseRTC
 *
 */
class RaspberryPiMouseRTCTest
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  RaspberryPiMouseRTCTest(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~RaspberryPiMouseRTCTest();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * 
   * - Name:  max_velocity
   * - DefaultValue: 0.2
   */
  double m_max_velocity;
  /*!
   * 
   * - Name:  max_acceleration
   * - DefaultValue: 0.52
   */
  double m_max_acceleration;
  /*!
   * 
   * - Name:  max_tangential_velocity
   * - DefaultValue: 0.52
   */
  double m_max_tangential_velocity;
  /*!
   * 
   * - Name:  max_tangential_acceleration
   * - DefaultValue: 0.314
   */
  double m_max_tangential_acceleration;
  /*!
   * 
   * - Name:  distance_of_wheels
   * - DefaultValue: 0.095
   */
  double m_distance_of_wheels;
  /*!
   * 
   * - Name:  diameter_of_wheel
   * - DefaultValue: 0.048
   */
  double m_diameter_of_wheel;
  /*!
   * 
   * - Name:  step_angle
   * - DefaultValue: 1.8
   */
  double m_step_angle;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedVelocity2D m_current_velocity_out;
  /*!
   */
  RTC::InPort<RTC::TimedVelocity2D> m_current_velocity_outIn;
  RTC::TimedPose2D m_current_pose_out;
  /*!
   */
  RTC::InPort<RTC::TimedPose2D> m_current_pose_outIn;
  RTC::TimedShortSeq m_ir_sensor_out;
  /*!
   */
  RTC::InPort<RTC::TimedShortSeq> m_ir_sensor_outIn;
  RTC::TimedBooleanSeq m_switch3bit_out;
  /*!
   */
  RTC::InPort<RTC::TimedBooleanSeq> m_switch3bit_outIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedVelocity2D m_target_velocity_in;
  /*!
   */
  RTC::OutPort<RTC::TimedVelocity2D> m_target_velocity_inOut;
  RTC::TimedPose2D m_pose_update_in;
  /*!
   */
  RTC::OutPort<RTC::TimedPose2D> m_pose_update_inOut;
  RTC::TimedShort m_buzzer_hz_in;
  /*!
   */
  RTC::OutPort<RTC::TimedShort> m_buzzer_hz_inOut;
  RTC::TimedBooleanSeq m_led4bit_in;
  /*!
   */
  RTC::OutPort<RTC::TimedBooleanSeq> m_led4bit_inOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void RaspberryPiMouseRTCTestInit(RTC::Manager* manager);
};

#endif // RASPBERRYPIMOUSERTC_TEST_H
