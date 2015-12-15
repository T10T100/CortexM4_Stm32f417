#include "guiEngine.h"
#include "touchScreenAdapter.h"
#include "touchSensorApiInterface.h"

void *guiEngine;

int sensorTouchHandler   (void *t)
{
    SensorAdapter *adapter = (SensorAdapter *)t;
    SensorDataStruct sensorData = adapter->getData();
    TouchStruct data = {
        sensorData.coordinates,
        sensorData.move,
        0,
        0
    };
    ((GuiEngine *)guiEngine)->fireSensorTouch(data);
}

int sensorClickHandler   (void *t)
{
    SensorAdapter *adapter = (SensorAdapter *)t;
    SensorDataStruct sensorData = adapter->getData();
    TouchStruct data = {
        sensorData.coordinates,
        sensorData.move,
        0,
        0
    };
    ((GuiEngine *)guiEngine)->fireSensorClick(data);
}

int sensorReleaseHandler   (void *t)
{
    SensorAdapter *adapter = (SensorAdapter *)t;
    SensorDataStruct sensorData = adapter->getData();
    TouchStruct data = {
        sensorData.coordinates,
        sensorData.move,
        0,
        0
    };
    ((GuiEngine *)guiEngine)->fireSensorRelease(data);
}

int sensorPressHandler   (void *t)
{
    SensorAdapter *adapter = (SensorAdapter *)t;
    SensorDataStruct sensorData = adapter->getData();
    TouchStruct data = {
        sensorData.coordinates,
        sensorData.move,
        0,
        0
    };
    ((GuiEngine *)guiEngine)->fireSensorPress(data);
}

void GuiEngine::setListeners ()
{
    vm::addSensorListener(sensorTouchHandler,   onAnyActionHandler);
    vm::addSensorListener(sensorClickHandler,   onClickHandler);
    vm::addSensorListener(sensorReleaseHandler, onReleaseHandler);
    vm::addSensorListener(sensorPressHandler,   onLongPress);
}




/*End of file*/

