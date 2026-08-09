#include <cstdint>

// بنية إعدادات النظام الصوتي وخوارزمية تنوير
struct TanweerCoreConfig {
    uint32_t sample_rate;      // معدل أخذ العينات (Hz)
    float sound_speed;         // سرعة الصوت (m/s)
    float mic_distance;        // المسافة بين الميكروفونات (m)
    int max_search_samples;    // نافذة البحث الزمنية (عينات)

    // مُهيئ افتراضي للقيم الأساسية
    TanweerCoreConfig()
        : sample_rate(44100),
          sound_speed(343.0f),
          mic_distance(0.05f),
          max_search_samples(60) {}
};

// مثال على استخدام Struct داخل الكود الرئيسي
TanweerCoreConfig core_settings;

int main() {
    // عرض الإعدادات للتأكد من تحميلها بشكل صحيح
    printf("FS = %u Hz | C = %.2f m/s | D = %.3f m | Window = %d samples\n",
           core_settings.sample_rate,
           core_settings.sound_speed,
           core_settings.mic_distance,
           core_settings.max_search_samples);

    return 0;
}
