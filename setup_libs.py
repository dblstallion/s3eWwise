import shutil
import os

iOS_Lib_Folder = os.path.join('Wwise', 'Wwise_v2014.1.1_build_5179', 'SDK-Apple', 'iOS')
iOS_Debug_Folder = os.path.join(iOS_Lib_Folder, 'Profile-iphoneos', 'lib')
iOS_Release_Folder = os.path.join(iOS_Lib_Folder, 'Release-iphoneos', 'lib')

Wp8_Lib_Folder = os.path.join('Wwise', 'Wwise_v2014.1.1_build_5179', 'SDK', 'WinPhone_ARM_vc110')
Wp8_Debug_Folder = os.path.join(Wp8_Lib_Folder, 'Profile', 'lib')
Wp8_Release_Folder = os.path.join(Wp8_Lib_Folder, 'Release', 'lib')

# Useful function
def forEachFile(dir, fn):
	for file in os.listdir(dir):
		file_path = os.path.join(dir, file)
		try:
			if os.path.isfile(file_path):
				fn(file_path)
		except Exception, e:
			print e
		
def copyTo(outputFolder):
	def outputFn(file_path):
		shutil.copy2(file_path, outputFolder)
	return outputFn
	
def copyToWithDebug(outputFolder):
	def outputFn(file_path):
		ext = os.path.splitext(os.path.basename(file_path))
		shutil.copy2(file_path, os.path.join(outputFolder, ext[0] + '_d' + ext[1]))
	return outputFn

print 'Setting up debug libraries for Marmalade'
print 'Copying from', iOS_Debug_Folder, 'to', iOS_Lib_Folder
forEachFile(iOS_Debug_Folder, copyToWithDebug(iOS_Lib_Folder))
print 'Copying from', iOS_Release_Folder, 'to', iOS_Lib_Folder
forEachFile(iOS_Release_Folder, copyTo(iOS_Lib_Folder))

print 'Copying from', Wp8_Debug_Folder, 'to', Wp8_Lib_Folder
forEachFile(Wp8_Debug_Folder, copyToWithDebug(Wp8_Lib_Folder))
print 'Copying from', Wp8_Release_Folder, 'to', Wp8_Lib_Folder
forEachFile(Wp8_Release_Folder, copyTo(Wp8_Lib_Folder))