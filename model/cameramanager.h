#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <QObject>

class CameraModel;
class CameraManager : public QObject
{
    Q_OBJECT
public:
    explicit CameraManager(QObject *parent = nullptr);
    ~CameraManager();
    static CameraManager *Instance(QObject* parent = nullptr);
    static void destory();
    CameraModel* model() const;

signals:


private:
    CameraModel* m_model;
    static CameraManager* _m;
};

#endif // CAMERAMANAGER_H
