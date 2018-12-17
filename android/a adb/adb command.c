1.adb 操作
推送文件
adb push <src> <des>
adb push E:\room\simple.ko	/system
adb push E:\room\simple		/system 			//推送文件夹里的所有文件
adb pull <src> <des>
adb pull /system/simple/simple.ko		E:\room\simple
adb pull /system/simple		E:\room\simple	//推送文件夹里的所有文件
