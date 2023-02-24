#include "cameramanager.h"
#include "cameramodel.h"

CameraManager *CameraManager::_m = nullptr;

CameraManager::CameraManager(QObject *parent) : QObject(parent), m_model(new CameraModel(this))
{

}

CameraManager::~CameraManager()
{

}

CameraManager *CameraManager::Instance(QObject *parent)
{
    if (!_m)
    {
        _m = new CameraManager(parent);
    }
    return _m;
}

void CameraManager::destory()
{
    if (_m)
    {
        _m->deleteLater();
    }
    _m = nullptr;
}

CameraModel *CameraManager::model() const
{
    return m_model;
}
