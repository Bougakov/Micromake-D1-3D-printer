# FAQ on Micromake D1 printer

This FAQ was written for [Facebook group of the owners of this cheap and great 3D printer](https://www.facebook.com/groups/173676226330714/). Unfortunately, Facebook sucks as a place to post large texts so I am placing them here. Feel free to send your pull requests if you want to add something.

### Variants of Micromake D1 and its “clones”:

Micromake D1 comes in  [3 versions](http://ali.ski/vzso1??&h=7AQHgTTr_&s=1):

*   cheapest “pulley” version (with wheels)
*   more expensive “linear rail” (with bearings)
*   and the most expensive “hiwin” (high quality rails are used)

Optionally printer can be shipped with heated bed which allows you to print with ABS type of plastic, and not just PLA. Heated bed comes with larger PSU that can supply 16.5A and replaces weak stock PSU.

Printers get shipped with either old or new type of main controller board.

### Things to consider before buying:

*   You can [earn cash back of about 5%](https://www.ebates.com/r/FACEBO550?eeid=28187) when buying 3D printer on AliExpress, using Ebates or other service. &#1056;&#1091;&#1089;&#1089;&#1082;&#1086;&#1103;&#1079;&#1099;&#1095;&#1085;&#1099;&#1077; &#1087;&#1086;&#1082;&#1091;&#1087;&#1072;&#1090;&#1077;&#1083;&#1080; &#1084;&#1086;&#1075;&#1091;&#1090; &#1087;&#1086;&#1083;&#1091;&#1095;&#1080;&#1090;&#1100; [&#1082;&#1101;&#1096;&#1073;&#1101;&#1082; 7% &#1085;&#1072; Letyshops.](https://www.facebook.com/notes/alexander-bgk/Ð¼ÐµÐ½Ñ-Ñ‚ÑƒÑ‚-Ð·Ð°ÐºÐ¸Ð´Ð°Ð»Ð¸-Ð¿Ñ€Ð¾ÑÑŒÐ±Ð°Ð¼Ð¸-Ñ€Ð°ÑÑÐºÐ°Ð·Ð°Ñ‚ÑŒ-cashbackÐ¸-Ð¾Ñ‚Ð²ÐµÑ‡Ð°ÑŽ/888117147961047)
*   Good discussions on what to buy with your Micromake: [here](https://www.facebook.com/groups/173676226330714/permalink/333773956987606/) and [here](https://www.facebook.com/groups/173676226330714/permalink/333812513650417/)

### Links to proven sellers:

*   [Official store](https://alitems.com/g/1e8d1144949a590a4ec116525dc3e8/?ulp=https%3A%2F%2Fwww.aliexpress.com%2Fstore%2Fproduct%2FMicromake-3D-printer-pulley-version-DIY-kit-Metal-Printer-3d-Printer-Kossel-Delta-3d-Printer-Kit%2F2128317_32647812923.html) (sells the original version in which all plastic parts are injection molded, with black oxidized aluminum profile)

### Buyer reviews:

Articles:

*   Review of HiWin version in Russian: [http://mysku.ru/blog/aliexpress/410...](http://mysku.ru/blog/aliexpress/41006.html)
*   Review of D1 purchased on TaoBao (in Russian): [http://mysku.ru/blog/aliexpress/394...](http://mysku.ru/blog/aliexpress/39495.html)
*   Review of heated bed upgrade in Russian: [http://mysku.ru/blog/aliexpress/431...](http://mysku.ru/blog/aliexpress/43168.html)

YouTube video reviews:

*   tbd

### Assembly guides:

*   There is a PDF assembly manual in English and in Russian on Google Drive (link in next section).
*   Official YouTube channel with instruction videos (English and Chinese): [https://www.youtube.com/channel/UCY...](https://www.youtube.com/channel/UCY9sDyEi81z3GjXhwGiP_RA/playlists) Note that original video files are in the official Google Drive folder.
*   Playlists in Chinese on Yoku: [http://www.youku.com/playlist_show/...](http://www.youku.com/playlist_show/id_23218776.html)

### Common assembly mistakes; tips & tricks:

*   There are 2 fans on the effector. One is used to constantly cool down the aluminum fins of the extruder. Second one will turn on just occasionally, to cool the model you print. Double check - the cooler that blows on the aluminum fins must be always on when printer is on.
*   For the best results disassemble the printing head. Take out the hot end and apply some thermal paste on the tip that goes into “cooling” part with aluminum fins (same thermal paste that goes between computer’s CPU and cooler). Wrap the other tip that goes into the square block with the heater into [teflon tape](http://3deshnik.ru/wp-content/uploads/2016/03/IMG_5992.jpg). This is the teflon tape that is used in the plumbing. This ensures the abrupt drop in the temperature between hot and cool zones of the hot end.

### Links to official software:

Assembly videos and official software are on Google Drive: [https://drive.google.com/drive/fold...](https://drive.google.com/drive/folders/0B1DQUrzkDP-tNDU0NXhVcGhlc0k?usp=sharing).

Google Drive [has](https://www.facebook.com/groups/173676226330714/permalink/304678969897105/?comment_id=304767046554964&comment_tracking={"tn":"R"}) <span class="_7xn">Repetier-Firmware version 0.92.9 and <span class="_7xn">Micromake version 2.0.2 at the time of writing.

GitHub repository of printer’s firmware (it is unknown whether it is fresh and/or original): [https://github.com/coldnew/MICROMAK...](https://github.com/coldnew/MICROMAKE)

Micromake uses custom modified software called “CURA” - this software was originally developed for Ultimaker brand of printers and was “borrowed” by Chinese company that makes Micromake D1\. “CURA” software has a special module used to calibrate printer and flash it with firmware. Please be aware that if you install heated bed upgrade, you need to enable checkbox in CURA and flash updated firmware to printer - see screenshot

![Bed upgrade checkbox](http://i.ebayimg.com/00/s/MTAwMFgxMDAw/z/RLcAAOSwNRdYA-gx/$_10.JPG?set_id=880000500F)

### How to auto-level and calibrate printer. Quality issues with prints and how to solve them:

Explanation of what “horizontal radius”, “diagonal rod length” and other terms mean: [https://forum.repetier.com/discussi...](https://forum.repetier.com/discussion/435/initial-delta-value-setup) (see illustrations!). There are different naming conventions, for example “horizontal radius” [is referred to as “delta radius” in other projects](https://www.facebook.com/groups/173676226330714/permalink/326322951066040/?comment_id=326351537729848&comment_tracking={"tn":"R"}).

Rod length should be [measured from hole to hole](https://www.facebook.com/groups/173676226330714/permalink/326218534409815/), on “pulley version” of Micromake D1 it is <span class="_7xn">215mm to <span class="_7xn">217mm (value in CURA is wrong, it says 210mm for some reason). Horizontal radius is about <span class="_7xn">95mm.

*   [Official YouTube video](https://www.youtube.com/watch?v=UFPXBdeJmg0) (in Chinese) that describes calibration process
*   [Another video](https://www.youtube.com/watch?v=TFeyNqYMFgU) (in English), describes calibration using CURA
*   [Online calculator](http://escher3d.com/pages/wizards/wizarddelta.php) that asks you to perform several measurements and gives you the adjustments you need to make
*   Some theory on calibrating delta printers: [http://minow.blogspot.de/](http://minow.blogspot.de/)
*   “Manual Delta Calibration using M665 and M666” (not tested) - YouTube [video (ignore OpenSCAD part in it)](https://www.youtube.com/watch?v=tDLbqLve128)
*   “[mini Kossel Calibration using Repetier FW](https://www.youtube.com/watch?v=uDB4hE6nyYI)”
*   “[Z-Leveling for Delta Printers with Repetier-Firmware](https://www.youtube.com/watch?v=L9URtv2LqKc)” by Repetier
*   OpenDACT(Delta Automatic Calibration Tool) - For Repetier - [description](http://forum.seemecnc.com/viewtopic.php?f=36&t=8698) demo
*   tbd

Typical problems with printing (classification of defects):

*   in English - [http://reprap.org/wiki/Print_Troubl...](http://reprap.org/wiki/Print_Troubleshooting_Pictorial_Guide)
*   in Russian - [http://3dtoday.ru/blogs/leoluch/defects-3d-printing-will-try-to-introduce-a-classification/](http://3dtoday.ru/blogs/leoluch/defects-3d-printing-will-try-to-introduce-a-classification/) 

### Hardware tweaks and modifications:

#### Body:

Replacing stock square nuts [with t-nuts](https://www.facebook.com/photo.php?fbid=10209986622366252&set=oa.287323128299356&type=3&theater)

#### Printing head and hot end (nozzle):

Micromake D1 uses “E3D V5” printing head. It is shipped with the standard copper nozzle with 0.4mm diameter. It has Teflon tube inside. (See photos in this Russian article on hot end types - [http://3deshnik.ru/blogs/akdzg/razn...](http://3deshnik.ru/blogs/akdzg/raznoobrazie-xotendov-e3d))

Consider buying a set of 0.2   0.3   0.4mm drill bits - they are useful with cleaning nozzle from debris.

#### Belts:

Micromake D1 uses “GT2” type belts.

*   Replacing pulley with [toothed version](https://www.facebook.com/groups/173676226330714/permalink/326137101084625/).

#### Rods:

Stock rods are 217mm in length.

*   Using [traxxas](https://www.facebook.com/groups/173676226330714/permalink/276316932733309/) rods instead of stock rods ([more detailed post](https://www.facebook.com/groups/173676226330714/permalink/276316912733311/))
*   Using additional [springs](https://www.facebook.com/photo.php?fbid=10209986622486255&set=oa.287323128299356&type=3&theater)
*   tbd

#### Heated bed:

*   You can greatly improve the speed of the warm-up if you place silicone mat or cork under the heated bed. It will also protect main board and wires from heat
*   Warm-up speed could also be greatly improved if you raise the voltage of the PSU from default 12V to 13.9V. It is safe for main board.

#### PSU:

*   Green power connector [is a fire hazard](http://3dtoday.ru/blogs/sanja/little-son-came-to-his-father-and-said-crumb/)! It is not rated for 16A current and will fry. Solder the thick copper wire (1.5mm2 - 2.5mm2 thick) to the board directly - there are dedicated pads. ([Link in English](https://www.facebook.com/groups/173676226330714/permalink/299971320367870/))
*   Using [connector from RC model](https://www.facebook.com/groups/173676226330714/permalink/323357818029220/) instead
*   You can put the PSU underneath the printer [with this simple mod (article in Russian with lots of photos)](http://3dtoday.ru/blogs/sanja/hide-the-power-supply-delta-printer-under-body/).

#### Upgrading effector:

*   [Magnetic joint](https://www.facebook.com/groups/173676226330714/permalink/320996994931969/) upgrade
*   [Adding light](https://www.facebook.com/groups/173676226330714/permalink/295700380794964/) LEDs
*   tbd

#### Placing the extruder so it is located conveniently. Adding spool holder.

[https://www.facebook.com/groups/173...](https://www.facebook.com/groups/173676226330714/permalink/323171281381207/)

#### Changing the auto-level mechanism to other type of probes:

*   Using [FSR](https://groups.google.com/forum/#!topic/deltabot/6fxnM20nYKc%5B1-25%5D) (force sensing resistors)
*   Using [weight sensors (in Russian)](http://3dtoday.ru/blogs/sanja/i-want-to-consult-about-the-installation-of-the-load-cell-weight-cell-/) ([in English](https://www.facebook.com/groups/173676226330714/)) - work in progress
*   [Mechanical Z-probe](https://www.facebook.com/groups/173676226330714/permalink/293425914355744/)
*   [Microswitch probe](https://www.facebook.com/groups/173676226330714/)
*   tbd

#### Stepper motor:

*   Microstepping (?): [https://www.facebook.com/zzcatvs/posts/995106527263309?pnref=story](https://www.facebook.com/zzcatvs/posts/995106527263309?pnref=story)

#### Changing main board to 24-bit versions:

Stock main board appears to be standard RAMPS 1.4.

*   [Upgrading to Duet](https://miscsolutions.wordpress.com/2015/01/04/upgrading-the-mini-kossel-to-duet-electronics-part-1-hardware/)
*   [MKS SBASE](https://www.facebook.com/groups/173676226330714/permalink/321204871577848/)
*   tbd

#### Adding remote control (Octoprint and others):

*   Step-by-step guide on installing OctoPrint on cheap Raspberry clone, Orange PI PC: [http://3dtoday.ru/blogs/eta4ever/orange-octopus-a-step-by-step-guide/](http://3dtoday.ru/blogs/eta4ever/orange-octopus-a-step-by-step-guide/)
*   tbd

### Software upgrades (changing CURA to other control software, different slicers)

Micromake’s representative in this group is [@zzcatvs](https://www.facebook.com/zzcatvs) He shared the latest firmware [in this post](https://www.facebook.com/groups/173676226330714/permalink/244973162534353/?comment_id=245027129195623&comment_tracking={"tn":"R9"}).

*   List of [other slicers](https://www.facebook.com/groups/173676226330714/permalink/320261655005503/) used by members of this group
*   [Settings for RepetierHost](https://www.facebook.com/groups/173676226330714/permalink/323009244730744/)
*   Mention of the [alternative “RichCal” firmware with autoleve feature](https://groups.google.com/forum/#!searchin/deltabot/micromake|sort:relevance/deltabot/AZHM_fai5fA/-T8T6h8pDAAJ) on Google Groups. ([Reported use of it by a member](https://www.facebook.com/groups/173676226330714/permalink/323855621312773/?comment_id=324436021254733&comment_tracking={"tn":"R"}))
*   [Marlin firmware](https://groups.google.com/forum/#!searchin/deltabot/micromake|sort:relevance/deltabot/AZHM_fai5fA/-T8T6h8pDAAJ)
*   Detailed walkthrough - setting up Simplify 3D to work with Micromake - [https://www.youtube.com/watch?v=zsq...](https://www.youtube.com/watch?v=zsqD5mTYO0E) (please note that author starts with deleting initial config).
*   Using Micromake D1 with KISSLICER - [https://youtu.be/vlvetkP1EkA](https://youtu.be/vlvetkP1EkA)
*   Installing RepetierHost and calibration: [https://www.youtube.com/watch?v=Nex...](https://www.youtube.com/watch?v=Nexaf7XOoPg)
*   tbd

### Other resources on the web:

*   Forum for Micromake D1 owners on Thingiverse: [<span class="_4yxr">http://www.thingiverse.com/groups/micromake/page:1](http://www.thingiverse.com/groups/micromake/page:1) there
*   [Reddit thread](https://www.reddit.com/r/3Dprinting/comments/4vrmsh/micromake_d1_or_alternative/) on Micromake
*   Wiki page on RepRap.org on “Kossel” family of delta printers - [http://reprap.org/wiki/Kossel](http://reprap.org/wiki/Kossel)
*   tbd
