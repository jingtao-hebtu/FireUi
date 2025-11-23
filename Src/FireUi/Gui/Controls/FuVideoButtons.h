#pragma once

#include <QPushButton>
#include <QString>

namespace TF
{
    class TechButtonBase : public QPushButton
    {
    public:
        explicit TechButtonBase(const QString& text, QWidget* parent = nullptr);

    protected:
        static QString buttonStyleSheet();
        void applySharedSetup();
    };

    class TechToggleButton : public TechButtonBase
    {
    public:
        explicit TechToggleButton(const QString& text, QWidget* parent = nullptr);
    };

    class TechActionButton : public TechButtonBase
    {
    public:
        explicit TechActionButton(const QString& text, QWidget* parent = nullptr);
    };
}
