
b
Command: %s
53*	vivadotcl21
opt_design -directive Explore2default:defaultZ4-113h px� 
d
$Directive used for opt_design is: %s67*	vivadotcl2
Explore2default:defaultZ4-136h px� 
�
@Attempting to get a license for feature '%s' and/or device '%s'
308*common2"
Implementation2default:default2
xczu9eg2default:defaultZ17-347h px� 
�
0Got license for feature '%s' and/or device '%s'
310*common2"
Implementation2default:default2
xczu9eg2default:defaultZ17-349h px� 
�
�The version limit for your license is '%s' and has expired for new software. A version limit expiration means that, although you may be able to continue to use the current version of tools or IP with this license, you will not be eligible for any updates or new releases.
719*common2
2019.082default:defaultZ17-1540h px� 
n
,Running DRC as a precondition to command %s
22*	vivadotcl2

opt_design2default:defaultZ4-22h px� 
R

Starting %s Task
103*constraints2
DRC2default:defaultZ18-103h px� 
P
Running DRC with %s threads
24*drc2
22default:defaultZ23-27h px� 
U
DRC finished with %s
272*project2
0 Errors2default:defaultZ1-461h px� 
d
BPlease refer to the DRC report (report_drc) for more information.
274*projectZ1-462h px� 
�

%s
*constraints2o
[Time (s): cpu = 00:00:10 ; elapsed = 00:00:06 . Memory (MB): peak = 1863.320 ; gain = 0.0002default:defaulth px� 
a

Starting %s Task
103*constraints2&
Logic Optimization2default:defaultZ18-103h px� 
E
%Done setting XDC timing constraints.
35*timingZ38-35h px� 
i

Phase %s%s
101*constraints2
1 2default:default2
Retarget2default:defaultZ18-101h px� 
w
)Pushed %s inverter(s) to %s load pin(s).
98*opt2
62default:default2
5852default:defaultZ31-138h px� 
K
Retargeted %s cell(s).
49*opt2
02default:defaultZ31-49h px� 
;
&Phase 1 Retarget | Checksum: 719ffabb
*commonh px� 
�

%s
*constraints2p
\Time (s): cpu = 00:00:26 ; elapsed = 00:00:20 . Memory (MB): peak = 1887.402 ; gain = 24.0822default:defaulth px� 
�
.Phase %s created %s cells and removed %s cells267*opt2
Retarget2default:default2
02default:default2
02default:defaultZ31-389h px� 
u

Phase %s%s
101*constraints2
2 2default:default2(
Constant propagation2default:defaultZ18-101h px� 
u
)Pushed %s inverter(s) to %s load pin(s).
98*opt2
02default:default2
02default:defaultZ31-138h px� 
G
2Phase 2 Constant propagation | Checksum: 3f2f9a69
*commonh px� 
�

%s
*constraints2p
\Time (s): cpu = 00:00:29 ; elapsed = 00:00:24 . Memory (MB): peak = 1887.402 ; gain = 24.0822default:defaulth px� 
�
.Phase %s created %s cells and removed %s cells267*opt2(
Constant propagation2default:default2
62default:default2
432default:defaultZ31-389h px� 
f

Phase %s%s
101*constraints2
3 2default:default2
Sweep2default:defaultZ18-101h px� 
8
#Phase 3 Sweep | Checksum: 3e77a8b0
*commonh px� 
�

%s
*constraints2p
\Time (s): cpu = 00:00:35 ; elapsed = 00:00:29 . Memory (MB): peak = 1887.402 ; gain = 24.0822default:defaulth px� 
�
.Phase %s created %s cells and removed %s cells267*opt2
Sweep2default:default2
02default:default2
7832default:defaultZ31-389h px� 
r

Phase %s%s
101*constraints2
4 2default:default2%
BUFG optimization2default:defaultZ18-101h px� 
D
/Phase 4 BUFG optimization | Checksum: 3e77a8b0
*commonh px� 
�

%s
*constraints2p
\Time (s): cpu = 00:00:38 ; elapsed = 00:00:32 . Memory (MB): peak = 1887.402 ; gain = 24.0822default:defaulth px� 
�
.Phase %s created %s cells and removed %s cells267*opt2%
BUFG optimization2default:default2
02default:default2
02default:defaultZ31-389h px� 
|

Phase %s%s
101*constraints2
5 2default:default2/
Shift Register Optimization2default:defaultZ18-101h px� 
N
9Phase 5 Shift Register Optimization | Checksum: 3e77a8b0
*commonh px� 
�

%s
*constraints2p
\Time (s): cpu = 00:00:40 ; elapsed = 00:00:34 . Memory (MB): peak = 1887.402 ; gain = 24.0822default:defaulth px� 
�
.Phase %s created %s cells and removed %s cells267*opt2/
Shift Register Optimization2default:default2
02default:default2
02default:defaultZ31-389h px� 
x

Phase %s%s
101*constraints2
6 2default:default2+
Post Processing Netlist2default:defaultZ18-101h px� 
J
5Phase 6 Post Processing Netlist | Checksum: 3e77a8b0
*commonh px� 
�

%s
*constraints2p
\Time (s): cpu = 00:00:41 ; elapsed = 00:00:35 . Memory (MB): peak = 1887.402 ; gain = 24.0822default:defaulth px� 
�
.Phase %s created %s cells and removed %s cells267*opt2+
Post Processing Netlist2default:default2
02default:default2
02default:defaultZ31-389h px� 
a

Starting %s Task
103*constraints2&
Connectivity Check2default:defaultZ18-103h px� 
�

%s
*constraints2s
_Time (s): cpu = 00:00:00 ; elapsed = 00:00:00.432 . Memory (MB): peak = 1887.402 ; gain = 0.0002default:defaulth px� 
I
4Ending Logic Optimization Task | Checksum: 3e77a8b0
*commonh px� 
�

%s
*constraints2p
\Time (s): cpu = 00:00:42 ; elapsed = 00:00:36 . Memory (MB): peak = 1887.402 ; gain = 24.0822default:defaulth px� 
Z
Releasing license: %s
83*common2"
Implementation2default:defaultZ17-83h px� 
�
G%s Infos, %s Warnings, %s Critical Warnings and %s Errors encountered.
28*	vivadotcl2
322default:default2
02default:default2
02default:default2
02default:defaultZ4-41h px� 
\
%s completed successfully
29*	vivadotcl2

opt_design2default:defaultZ4-42h px� 
�
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2 
opt_design: 2default:default2
00:01:002default:default2
00:00:502default:default2
1887.4022default:default2
24.0822default:defaultZ17-268h px� 
H
&Writing timing data to binary archive.266*timingZ38-480h px� 
�
 The %s '%s' has been generated.
621*common2

checkpoint2default:default2h
TD:/SABER_FPGA_cleaned_for_Github/project_1/project_1.runs/impl_1/Top_wrapper_opt.dcp2default:defaultZ17-1381h px� 
�
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2&
write_checkpoint: 2default:default2
00:00:232default:default2
00:00:172default:default2
1887.4022default:default2
0.0002default:defaultZ17-268h px� 
�
%s4*runtcl2�
sExecuting : report_drc -file Top_wrapper_drc_opted.rpt -pb Top_wrapper_drc_opted.pb -rpx Top_wrapper_drc_opted.rpx
2default:defaulth px� 
�
Command: %s
53*	vivadotcl2z
freport_drc -file Top_wrapper_drc_opted.rpt -pb Top_wrapper_drc_opted.pb -rpx Top_wrapper_drc_opted.rpx2default:defaultZ4-113h px� 
P
Running DRC with %s threads
24*drc2
22default:defaultZ23-27h px� 
�
#The results of DRC are in file %s.
168*coretcl2�
ZD:/SABER_FPGA_cleaned_for_Github/project_1/project_1.runs/impl_1/Top_wrapper_drc_opted.rptZD:/SABER_FPGA_cleaned_for_Github/project_1/project_1.runs/impl_1/Top_wrapper_drc_opted.rpt2default:default8Z2-168h px� 
\
%s completed successfully
29*	vivadotcl2

report_drc2default:defaultZ4-42h px� 
�
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2 
report_drc: 2default:default2
00:00:292default:default2
00:00:162default:default2
1887.4022default:default2
0.0002default:defaultZ17-268h px� 


End Record