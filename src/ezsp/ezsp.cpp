/**
 * @file ezsp.cpp
 * 
 * @brief Facade for NSEZSP::CLibEzspMain, hiding its internals in the published headers
 */

#include "ezsp/ezsp.h"
#include "ezsp/lib-ezsp-main.h"

using NSEZSP::CEzsp;

CEzsp::CEzsp(NSSPI::IUartDriver* uartDriver, const NSSPI::TimerBuilder& timerbuilder, unsigned int requestZbNetworkResetToChannel)
{
#ifndef DYNAMIC_ALLOCATION
	static CLibEzspMain g_MainEzsp(uartDriver, timerbuilder, requestZbNetworkResetToChannel);
	main = &g_MainEzsp;
#else
	main = new CLibEzspMain(uartDriver, timerbuilder, requestZbNetworkResetToChannel);

	/* Memory leak here, if DYNAMIC_ALLOCATION is defined, main is allocated but never de-allocated */
#endif
}

void CEzsp::start()
{
	main->start();
}

void CEzsp::forceFirmwareUpgradeOnInitTimeout()
{
	main->forceFirmwareUpgradeOnInitTimeout();
}

void CEzsp::registerLibraryStateCallback(FLibStateCallback newObsStateCallback)
{
	main->registerLibraryStateCallback(newObsStateCallback);
}

void CEzsp::registerGPFrameRecvCallback(FGpFrameRecvCallback newObsStateCallback)
{
	main->registerGPFrameRecvCallback(newObsStateCallback);
}

void CEzsp::registerGPSourceIdCallback(FGpSourceIdCallback newObsGPSourceIdCallback)
{
	main->registerGPSourceIdCallback(newObsGPSourceIdCallback);
}

bool CEzsp::clearAllGPDevices()
{
	return main->clearAllGPDevices();
}

bool CEzsp::removeGPDevices(const std::vector<uint32_t>& sourceIdList)
{
	return main->removeGPDevices(sourceIdList);
}

bool CEzsp::addGPDevices(const std::vector<CGpDevice> &gpDevicesList)
{
	return main->addGPDevices(gpDevicesList);
}

bool CEzsp::openCommissioningSession()
{
	return main->openCommissioningSession();
}

bool CEzsp::closeCommissioningSession()
{
	return main->closeCommissioningSession();
}

void CEzsp::setAnswerToGpfChannelRqstPolicy(bool allowed)
{
	main->setAnswerToGpfChannelRqstPolicy(allowed);
}

void CEzsp::setFirmwareUpgradeMode()
{
	main->setFirmwareUpgradeMode();
}

bool CEzsp::startEnergyScan(FEnergyScanCallback energyScanCallback, uint8_t duration)
{
	return main->startEnergyScan(energyScanCallback, duration);
}

bool CEzsp::setChannel(uint8_t channel) {
	return main->setChannel(channel);
}
