# 
# Report generation script generated by Vivado
# 

proc create_report { reportName command } {
  set status "."
  append status $reportName ".fail"
  if { [file exists $status] } {
    eval file delete [glob $status]
  }
  send_msg_id runtcl-4 info "Executing : $command"
  set retval [eval catch { $command } msg]
  if { $retval != 0 } {
    set fp [open $status w]
    close $fp
    send_msg_id runtcl-5 warning "$msg"
  }
}
proc start_step { step } {
  set stopFile ".stop.rst"
  if {[file isfile .stop.rst]} {
    puts ""
    puts "*** Halting run - EA reset detected ***"
    puts ""
    puts ""
    return -code error
  }
  set beginFile ".$step.begin.rst"
  set platform "$::tcl_platform(platform)"
  set user "$::tcl_platform(user)"
  set pid [pid]
  set host ""
  if { [string equal $platform unix] } {
    if { [info exist ::env(HOSTNAME)] } {
      set host $::env(HOSTNAME)
    }
  } else {
    if { [info exist ::env(COMPUTERNAME)] } {
      set host $::env(COMPUTERNAME)
    }
  }
  set ch [open $beginFile w]
  puts $ch "<?xml version=\"1.0\"?>"
  puts $ch "<ProcessHandle Version=\"1\" Minor=\"0\">"
  puts $ch "    <Process Command=\".planAhead.\" Owner=\"$user\" Host=\"$host\" Pid=\"$pid\">"
  puts $ch "    </Process>"
  puts $ch "</ProcessHandle>"
  close $ch
}

proc end_step { step } {
  set endFile ".$step.end.rst"
  set ch [open $endFile w]
  close $ch
}

proc step_failed { step } {
  set endFile ".$step.error.rst"
  set ch [open $endFile w]
  close $ch
}

set_msg_config -id {Common 17-41} -limit 10000000
set_msg_config -id {HDL-1065} -limit 10000

start_step init_design
set ACTIVE_STEP init_design
set rc [catch {
  create_msg_db init_design.pb
  set_param power.enableUnconnectedCarry8PinPower 1
  set_param power.BramSDPPropagationFix 1
  set_param power.enableCarry8RouteBelPower 1
  set_param power.enableLutRouteBelPower 1
  create_project -in_memory -part xczu9eg-ffvb1156-2-e
  set_property board_part xilinx.com:zcu102:part0:3.2 [current_project]
  set_property design_mode GateLvl [current_fileset]
  set_param project.singleFileAddWarning.threshold 0
  set_property webtalk.parent_dir D:/SABER_FPGA_cleaned_for_Github/project_1/project_1.cache/wt [current_project]
  set_property parent.project_path D:/SABER_FPGA_cleaned_for_Github/project_1/project_1.xpr [current_project]
  set_property ip_repo_paths {
  D:/SABER_FPGA_cleaned_for_Github/ip_repo/AXI_Slave8Ports_1.0
  D:/SABER_FPGA_cleaned_for_Github/ip_repo/AXIslave_1.0
} [current_project]
  set_property ip_output_repo D:/SABER_FPGA_cleaned_for_Github/project_1/project_1.cache/ip [current_project]
  set_property ip_cache_permissions {read write} [current_project]
  set_property XPM_LIBRARIES {XPM_CDC XPM_FIFO XPM_MEMORY} [current_project]
  add_files -quiet D:/SABER_FPGA_cleaned_for_Github/project_1/project_1.runs/synth_1/Top_wrapper.dcp
  set_msg_config -source 4 -id {BD 41-1661} -limit 0
  set_param project.isImplRun true
  read_ip -quiet D:/SABER_FPGA_cleaned_for_Github/project_1/project_1.srcs/sources_1/ip/INS_RAM/INS_RAM.xci
  read_ip -quiet D:/SABER_FPGA_cleaned_for_Github/project_1/project_1.srcs/sources_1/ip/BRAM64_1024/BRAM64_1024.xci
  add_files D:/SABER_FPGA_cleaned_for_Github/project_1/project_1.srcs/sources_1/bd/Top/Top.bd
  set_param project.isImplRun false
  set_param project.isImplRun true
  link_design -top Top_wrapper -part xczu9eg-ffvb1156-2-e
  set_param project.isImplRun false
  write_hwdef -force -file Top_wrapper.hwdef
  close_msg_db -file init_design.pb
} RESULT]
if {$rc} {
  step_failed init_design
  return -code error $RESULT
} else {
  end_step init_design
  unset ACTIVE_STEP 
}

start_step opt_design
set ACTIVE_STEP opt_design
set rc [catch {
  create_msg_db opt_design.pb
  opt_design -directive Explore
  write_checkpoint -force Top_wrapper_opt.dcp
  create_report "impl_1_opt_report_drc_0" "report_drc -file Top_wrapper_drc_opted.rpt -pb Top_wrapper_drc_opted.pb -rpx Top_wrapper_drc_opted.rpx"
  close_msg_db -file opt_design.pb
} RESULT]
if {$rc} {
  step_failed opt_design
  return -code error $RESULT
} else {
  end_step opt_design
  unset ACTIVE_STEP 
}

start_step place_design
set ACTIVE_STEP place_design
set rc [catch {
  create_msg_db place_design.pb
  if { [llength [get_debug_cores -quiet] ] > 0 }  { 
    implement_debug_core 
  } 
  place_design -directive Explore
  write_checkpoint -force Top_wrapper_placed.dcp
  create_report "impl_1_place_report_io_0" "report_io -file Top_wrapper_io_placed.rpt"
  create_report "impl_1_place_report_utilization_0" "report_utilization -file Top_wrapper_utilization_placed.rpt -pb Top_wrapper_utilization_placed.pb"
  create_report "impl_1_place_report_control_sets_0" "report_control_sets -verbose -file Top_wrapper_control_sets_placed.rpt"
  close_msg_db -file place_design.pb
} RESULT]
if {$rc} {
  step_failed place_design
  return -code error $RESULT
} else {
  end_step place_design
  unset ACTIVE_STEP 
}

start_step phys_opt_design
set ACTIVE_STEP phys_opt_design
set rc [catch {
  create_msg_db phys_opt_design.pb
  phys_opt_design -directive Explore
  write_checkpoint -force Top_wrapper_physopt.dcp
  close_msg_db -file phys_opt_design.pb
} RESULT]
if {$rc} {
  step_failed phys_opt_design
  return -code error $RESULT
} else {
  end_step phys_opt_design
  unset ACTIVE_STEP 
}

start_step route_design
set ACTIVE_STEP route_design
set rc [catch {
  create_msg_db route_design.pb
  route_design -directive Explore
  write_checkpoint -force Top_wrapper_routed.dcp
  create_report "impl_1_route_report_drc_0" "report_drc -file Top_wrapper_drc_routed.rpt -pb Top_wrapper_drc_routed.pb -rpx Top_wrapper_drc_routed.rpx"
  create_report "impl_1_route_report_methodology_0" "report_methodology -file Top_wrapper_methodology_drc_routed.rpt -pb Top_wrapper_methodology_drc_routed.pb -rpx Top_wrapper_methodology_drc_routed.rpx"
  create_report "impl_1_route_report_power_0" "report_power -file Top_wrapper_power_routed.rpt -pb Top_wrapper_power_summary_routed.pb -rpx Top_wrapper_power_routed.rpx"
  create_report "impl_1_route_report_route_status_0" "report_route_status -file Top_wrapper_route_status.rpt -pb Top_wrapper_route_status.pb"
  create_report "impl_1_route_report_timing_summary_0" "report_timing_summary -max_paths 10 -file Top_wrapper_timing_summary_routed.rpt -pb Top_wrapper_timing_summary_routed.pb -rpx Top_wrapper_timing_summary_routed.rpx -warn_on_violation "
  create_report "impl_1_route_report_incremental_reuse_0" "report_incremental_reuse -file Top_wrapper_incremental_reuse_routed.rpt"
  create_report "impl_1_route_report_clock_utilization_0" "report_clock_utilization -file Top_wrapper_clock_utilization_routed.rpt"
  create_report "impl_1_route_report_bus_skew_0" "report_bus_skew -warn_on_violation -file route_report_bus_skew_0.rpt -rpx route_report_bus_skew_0.rpx"
  close_msg_db -file route_design.pb
} RESULT]
if {$rc} {
  write_checkpoint -force Top_wrapper_routed_error.dcp
  step_failed route_design
  return -code error $RESULT
} else {
  end_step route_design
  unset ACTIVE_STEP 
}

start_step write_bitstream
set ACTIVE_STEP write_bitstream
set rc [catch {
  create_msg_db write_bitstream.pb
  set_property XPM_LIBRARIES {XPM_CDC XPM_FIFO XPM_MEMORY} [current_project]
  catch { write_mem_info -force Top_wrapper.mmi }
  write_bitstream -force Top_wrapper.bit 
  catch { write_sysdef -hwdef Top_wrapper.hwdef -bitfile Top_wrapper.bit -meminfo Top_wrapper.mmi -file Top_wrapper.sysdef }
  catch {write_debug_probes -quiet -force Top_wrapper}
  catch {file copy -force Top_wrapper.ltx debug_nets.ltx}
  close_msg_db -file write_bitstream.pb
} RESULT]
if {$rc} {
  step_failed write_bitstream
  return -code error $RESULT
} else {
  end_step write_bitstream
  unset ACTIVE_STEP 
}
