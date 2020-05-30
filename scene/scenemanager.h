#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "scene.h"

#include <QObject>

class SceneManager : public QObject
{
    Q_OBJECT

public:
    SceneManager();
    virtual ~SceneManager();


protected:
    void CreateScene();
    Scene *GetScene(QString &);

private:
#pragma region SCENE_FIELDS

    /*!
     * \brief m_sceneMap 씬 목록
     */
    QMap<QString, Scene &> m_sceneMap;

#pragma endregion SCENE_FIELDS
};

#endif // SCENEMANAGER_H
