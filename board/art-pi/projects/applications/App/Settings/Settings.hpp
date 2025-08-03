/*
 * @Author: huangjian huangjian921@outlook.com
 * @Date: 2025-08-02
 * @File: App/Settings/Settings.hpp
 * @Description: Settings header file for the application.
 */
#pragma once

class Settings {
public:
    Settings();
    ~Settings();
    void init();
    void show();
    void handleEvent(int event);
private:
    void createUI();
    void updateSettings();
    void openSettingItem(int index);
    void closeSettings();
    void onSettingItemClicked(int index);
    void refreshUI();
    void loadSettings();
};
