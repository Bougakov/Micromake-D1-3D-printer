Part two. Continues from "[Patching and installing Micromake D1 firmware (Repetier)](https://github.com/Bougakov/Micromake-D1-3D-printer/blob/master/Installing%20custom%20firmware%.md)"

# Calibrating Micromake D1 using OpenDACT utility

Obtain the OpenDACT utility here - http://forum.seemecnc.com/viewtopic.php?f=36&t=8698 You will need version `2.0.5A`. Download the distribution, unzip it into convenient location and execute `setup.exe` first. Then, run `Delta Kinematics Calibration Tool.exe`.

## Fix errors with non-US locale

OpenDACT has a bug - because it was written by an American, it assumes that the decimal part in integers is separated by the *point* character. Yet in Russia and few other countries *comma* is used as decimal separator instead. Once the software meets an unexpected symbol, it crashes. Author has been notified about this bug - https://github.com/RollieRowland/OpenDACT/issues/13 - but unless fixed, it can be circumvented by changing "locale settings" in Windows. Apply this fix if you are affected by this bug:

![Screenshot](https://cloud.githubusercontent.com/assets/1763243/20276440/4d898040-aaad-11e6-83a2-d61963abfb82.png)

## Let's reset EEPROM settings to defaults before calibration

Save your current settings to a file or write them down in case you'd want to have them back. 

I strongly suggest resetting all values to defaults so OpenDACT will be starting from scratch. This list of g-codes will do the job; alternatively you can alter them manually:

    M206 T3 P153 X312.000   ; Z max length [mm]
    M206 T1 P893 S000       ; Tower X endstop offset [steps]
    M206 T1 P895 S000       ; Tower Y endstop offset [steps]
    M206 T1 P897 S000       ; Tower Z endstop offset [steps]
    M206 T3 P881 X217.000   ; Diagonal rod length [mm]
    M206 T3 P885 X95.2      ; Horizontal rod radius at 0,0 [mm]
    M206 T3 P901 X210.00    ; Alpha A(210):
    M206 T3 P905 X330.00    ; Alpha B(330):
    M206 T3 P909 X90.000    ; Alpha C(90):
    M206 T3 P913  X0.000    ; Delta Radius A(0):
    M206 T3 P917  X0.000    ; Delta Radius B(0):
    M206 T3 P921  X0.000    ; Delta Radius C(0):
    M206 T3 P933  X0.000    ; Corr. diagonal A [mm]
    M206 T3 P937  X0.000    ; Corr. diagonal B [mm] 
    M206 T3 P941  X0.000    ; Corr. diagonal C [mm] 
    M206 T3 P808  X0.000    ; Z-probe height [mm] 

Please ensure that the "steps per mm" parameter is correctly set - it can be corrupted during firmware upgrade!

## Important note on Z-probe

If you are using stock Z-probe, skip this section.

If you are using snap-on Z-probe, please ensure that `Z-probe height [mm]` is set to zero in your printer's EEPROM, and the value of `Z max length [mm]` is decreased by the probe's height.

For example, my printer's height is 311.82mm. [The "teddybear" Z-probe](https://www.facebook.com/groups/173676226330714/permalink/371138909917777/) I am using is attached below on a hinge, its height is 12.4mm. I subtracted 12.4 from the original height and got 293.42mm, - I entered this new value into EEPROM as the new `Z max length [mm]`.

![Teddy with boner](https://scontent-ams3-1.xx.fbcdn.net/v/t1.0-9/16195531_10158495767570354_6174518943208334893_n.jpg?oh=798154abea958b18114b8c29e6ea8d4f&oe=59636BB6)

*(If you like this design of the Z-probe, you can purchase it from [Pinshape](https://pinshape.com/items/31151-3d-printed-z-eddy-the-micromake-z-probe-e3d-v5-fits-afinibot-etc). It is totally worth the asking price.).*

## Calibrate the printer with OpenDACT

Launch the program. In the `Build diameter` enter the diameter of the circle you'd like to probe during calibration. _Don't be greedy_, there is no point in probing the edges of the glass. The design of the delta makes the effector bend on the edges of the plate making the measurements inaccurate. The diameter of 100 - 120mm is perfectly enough!

In `Diagonal rod` field enter `217`. Select the correct port and choose `Baud rate` of `250 000`. Hit `Connect`.

Then hit `Advanced`. Ensure that `Z-minimum type` is set to `FSR` (and [not](https://github.com/RollieRowland/OpenDACT/issues/14#issuecomment-288098600) `Z-probe`!), and fields `FSR plate offset` amd `Z-probe height` are set to zero. 

`Z-probe start height` sets the height starting from which printer moves its effector very slowly. If you set it too high, calibration will proceed slower. Setting it too low creates the risk of full speed collision of the nozzle and the glass. Use your discretion when setting this.

Once you've set the values, hit `Calibrate` (but not `A.I. Calibrate` and not `H.A.I. Calibrate`). The rest will be done automatically.

![OpenDact - 1st screenshot](https://raw.githubusercontent.com/Bougakov/Micromake-D1-3D-printer/master/opendact1.png)

You can see for yourself how flawed your build is by looking at the values on the second tab:

![OpenDact - 2nd screenshot](https://raw.githubusercontent.com/Bougakov/Micromake-D1-3D-printer/master/opendact2.png)

## Final notes

Утилита OpenDACT - кривая и глючная, вылетает при любом чихе. Но дело своё делает, так что смиритесь. Если у вас есть навыки в разработке на C# - пожалуйста, помогите автору исправлять баги. Код открыт и выложен на https://github.com/RollieRowland/OpenDACT

Ссылка на обсуждение статьи в VK - https://vk.com/micromake_d1?w=wall-134740295_7428

## И напоследок - выставляем правильную высоту печати

Положите на стекло плотный кусочек бумаги. Полоска "альбомной" бумаги или кусок обложки журнала - лучше всего. Через меню на LCD-кране принтера зайдите в пункт, `Configuration` -> `Z calib.` -> `Z position`.

Аккуратно, будто вы герой фильма про ограбление банка, опустите сопло вниз, чтобы оно прижало бумажку к стеклу. Не переусердствуйте, крутите ручку нежно и медленно, чтобы не засадить сопло в стол. Если не получилось и эффектор перекосило, дайте команду `Home all` и начните снова.

![Bank heist](https://raw.githubusercontent.com/Bougakov/Micromake-D1-3D-printer/master/images/lock%20artist.jpg)

Ваша задача - опустить сопло так, чтобы бумажку слегка прижало соплом - но чтобы её можно было легко протащить пальцами без усилия.

## Если вам хочется убедиться, что принтер реально откалиброван, не печатая тестовую "тарелку":

Вы можете заставить его промерять всю площадь стола датчиком. Я написал утилиту, которая делает такие вот карты высот:

![Height map](https://raw.githubusercontent.com/Bougakov/Micromake-D1-3D-printer/master/visualize/23%20OpenDACT.png)

Утилиты выложены на https://github.com/Bougakov/Micromake-D1-3D-printer/tree/master/visualize#tool-for-creating-easy-to-analyze-delta-kossel-bed-distortion-heat-maps 

Вам понадобятся Microsoft Excel и Python3. Мои скрипты очень сырые, не судите строго.

 * Сначала джаваскриптом генерируется g-code - получается маршрут для "прощупывания" стола по спирали
 * вы этот g-code скармливаете принтеру, он его исполняет. После исполнения кода принтер сложит результаты замеров в лог.
 * Лог надо почистить в Экселе, чтобы осталось 3 колонки цифр - замер высоты, координата по X и координата по Y.
 * Сохраните 3 колонки в tab-delimited CSV-файл и скормите скрипту на питоне (впишите имя CSV-файла в код скрипта).
 * Запустите скрипт и он построит график с помощью mathplotlib
 
Если вы хорошо пишете на Python и сможете доработать скрипт так, чтобы он:

 * Превратился бы в GUI-приложение
 * Имел бы поле, в которое можно было бы вставить лог принтера "как есть"
 * Умел бы парсить этот лог и доставать только нужные строчки
 
...то все вам будут очень благодарны. Присылайте пулл-реквесты.
