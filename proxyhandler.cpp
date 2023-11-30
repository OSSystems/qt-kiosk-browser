#include "proxyhandler.hpp"

void ProxyHandler::printCurrentProxySettings()
{
    if (QNetworkProxyFactory::usesSystemConfiguration())
    {
        qDebug() << "Using system proxy configuration.";
    }
    else
    {
        qDebug() << "Using custom proxy configuration.";
    }

    QNetworkProxy proxy = QNetworkProxy::applicationProxy();
    qDebug() << "Proxy type:" << proxy.type();
    qDebug() << "Proxy host:" << proxy.hostName();
    qDebug() << "Proxy port:" << proxy.port();
    qDebug() << "Proxy user:" << proxy.user();
    qDebug() << "Proxy password:" << proxy.password();
}

Q_INVOKABLE void ProxyHandler::useSystemProxy()
{
    QByteArray proxyUrl = qgetenv("https_proxy");

    qDebug() << "Proxy URL: " << proxyUrl;
    if (!proxyUrl.isEmpty())
    {
        QUrl url{QString(proxyUrl)};
        qDebug() << "Proxy URL is not empty: " << url;

        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::HttpProxy);
        proxy.setHostName(url.host());
        proxy.setPort(url.port());

        if (!url.userName().isEmpty())
        {
            proxy.setUser(url.userName());
        }
        if (!url.password().isEmpty())
        {
            proxy.setPassword(url.password());
        }
        qDebug() << "Proxy: " << proxy;

        QNetworkProxy::setApplicationProxy(proxy);
    }
    qDebug() << "application proxy is" << QNetworkProxy::applicationProxy();
    qDebug() << "Done setting use system proxy to true";
}