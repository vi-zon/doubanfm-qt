#ifndef DOUBAN_H
#define DOUBAN_H

#include <QObject>
#include <QNetworkAccessManager>
#include "douban_types.h"
#include <memory>

static const unsigned int DOUBAN_MANAGER_ARRAY_SIZE = 9;

class DoubanFM : public QObject
{
    Q_OBJECT
public:
    ~DoubanFM();
    static DoubanFM *getInstance();

    void userLogin(const QString &email, const QString &password);
    void userLogout();
    void userReLogin();

    void getNewPlayList(const qint32 &channel);
    void getPlayingList(const qint32& channel, const quint32& sid);
    void rateSong(const quint32& sid, const qint32& channel, const bool toRate);
    void unrateSong(const quint32& sid, const qint32& channel);
    void skipSong(const quint32& sid, const qint32& channel);
    void songEnd(const quint32& sid, const qint32& channel);
    void byeSong(const quint32& sid, const qint32& channel);

    void getChannels();

    void setUser(std::shared_ptr<DoubanUser> user);
    std::shared_ptr<DoubanUser> getUser();
    bool hasLogin();
    
signals:
    void receivedNewList(const QList<DoubanFMSong>& songs);
    void receivedPlayingList(const QList<DoubanFMSong>& songs);
    void receivedRateSong(bool succeed);
    void receivedSkipSong(bool succeed);
    void receivedCurrentEnd(bool succeed);
    void receivedByeSong(bool succeed);
    void receivedChannels(const QList<DoubanChannel>& channels);
    void loginSucceed(std::shared_ptr<DoubanUser> user);
    void loginFailed(const QString &errmsg);
    void logoffSucceed();
    
private slots:
    void onReceivedAuth(QNetworkReply *reply);
    void onReceivedRelogin(QNetworkReply *reply);
    void onReceivedNewList(QNetworkReply *reply);
    void onReceivedPlayingList(QNetworkReply *reply);
    void onReceivedRateSong(QNetworkReply *reply);
    void onReceivedSkipSong(QNetworkReply *reply);
    void onReceivedCurrentEnd(QNetworkReply *reply);
    void onReceivedByeSong(QNetworkReply *reply);
    void onReceivedChannels(QNetworkReply *reply);

    void onLoginSucceed(std::shared_ptr<DoubanUser> user);

private:
    explicit DoubanFM(QObject *parent = 0);
    /**
     * @brief _managers
     *
     * 0: User Relogin
     * 1: new list
     * 2: rate song/unrate song
     * 3: skip song
     * 4: current end
     * 5: bye song
     * 6: get channels
     * 7: playing list
     * 8: Login/Logout
     */
    QNetworkAccessManager *_managers[DOUBAN_MANAGER_ARRAY_SIZE];

    std::shared_ptr<DoubanUser> _user;
};



#endif // DOUBAN_H
