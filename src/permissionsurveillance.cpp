#include "permissionsurveillance.h"
#include <QDebug>

PermissionSurveillance::PermissionSurveillance(QObject *parent)
    : QObject{parent}
{
    m_permissionSurveillanceVisible = false;
    m_screenCaptureVisible = false;
    //寤虹珛鍒皊ession bus鐨勮繛鎺?
    QDBusConnection connection = QDBusConnection::sessionBus();
    if(!connection.registerService("org.lingmo.Statusbar"))
    {
        qDebug() << "error:" << connection.lastError().message();
    }
    if(!connection.registerObject("/Statusbar/PermissionSurveillance", this,QDBusConnection::ExportAllSlots))
    {
        qDebug() << "error:瀵硅薄娉ㄥ唽澶辫触";
    }
}

void PermissionSurveillance::sendCameraUser(QString text)
{
    qDebug() << "鎺ュ彈鍒扮浉鏈轰娇鐢ㄤ俊鍙凤紒锛侊紒";
    if(text=="{U-APPLE_QAQ-U}")
    {
        m_permissionSurveillanceVisible = false;
        m_cameraUser = "";
        emit PermissionSurveillanceVisibleChanged();
        emit cameraUserChanged();
        return;
    }
    m_permissionSurveillanceVisible = true;
    emit PermissionSurveillanceVisibleChanged();
    m_cameraUser = text;
    emit cameraUserChanged();
}

void PermissionSurveillance::sendScreenCaptureUser(QString text)
{
    qDebug() << "鎺ュ彈鍒板睆骞曟崟鑾蜂俊鍙凤紒锛侊紒";
    if(text=="{U-APPLE_QAQ-U}")
    {
        m_screenCaptureVisible = false;
        m_screenCaptureUser = "";
        emit screenCaptureVisibleChanged();
        emit screenCaptureUserChanged();
        return;
    }
    m_screenCaptureVisible = true;
    emit screenCaptureVisibleChanged();
    m_screenCaptureUser = text;
    emit screenCaptureUserChanged();
}

QString PermissionSurveillance::getCameraUser()
{
    return m_cameraUser;
}

bool PermissionSurveillance::getPermissionSurveillanceVisible()
{
    return m_permissionSurveillanceVisible;
}

QString PermissionSurveillance::getScreenCaptureUser()
{
    return m_screenCaptureUser;
}

bool PermissionSurveillance::getScreenCaptureVisible()
{
    return m_screenCaptureVisible;
}
