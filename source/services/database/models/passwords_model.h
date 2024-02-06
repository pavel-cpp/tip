#pragma once

// Qt
#include <QStringList>

class SettingsManager;

namespace Models {
    class Passwords {
    public:
        const QStringList &GetPasswords() const {
            return passwords;
        }

    private:
        friend class ::SettingsManager;

        QStringList passwords = {"root"};
    };
}
