"%WWISEROOT%\Authoring\Win32\Release\bin\WwiseCLI.exe" ..\Wwise\Wwise_v2013.2.10_build_4884\SDK\samples\IntegrationDemo\WwiseProject\IntegrationDemo.wproj -GenerateSoundBanks
xcopy ..\Wwise\Wwise_v2013.2.10_build_4884\SDK\samples\IntegrationDemo\WwiseProject\GeneratedSoundBanks\* data\\Audio /s /i /y