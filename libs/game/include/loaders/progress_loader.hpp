#pragma once

#include <string>
#include <vector>

namespace game {
    struct level_stat {
        unsigned int num;
        unsigned int time_as_seconds;
        unsigned char stars;
        bool is_win;

        bool operator==(const level_stat &b) const {
            return num == b.num && time_as_seconds == b.time_as_seconds &&
                   is_win == b.is_win && stars == b.stars;
        }

        level_stat() = default;

        level_stat(unsigned int num, unsigned int time, unsigned char stars, bool is_win) :
                num(num),
                time_as_seconds(time),
                stars(stars),
                is_win(is_win) {}
    };

    struct progress_t {
        size_t coins;
        std::vector<level_stat> levels;

        bool is_empty() {
            return !coins && levels.empty();
        }

        friend bool operator==(const progress_t &a, const progress_t &b) {
            bool is_eq = a.coins == b.coins;
            if (is_eq) {
                is_eq = a.levels.size() == b.levels.size();
                if (is_eq) {
                    for (size_t i = 0; (i < a.levels.size()) && is_eq; ++i) {
                        is_eq = a.levels[i] == b.levels[i];
                    }
                }
            }
            return is_eq;
        }
    };

    class ProgressLoader {
    public:
        virtual progress_t load(size_t player_id) = 0;

        virtual void save(size_t player_id, progress_t &progress) = 0;

        virtual ~ProgressLoader() = default;

    };

    class BaseProgressLoader : public ProgressLoader {
    public:
        BaseProgressLoader() = default;

        ~BaseProgressLoader() override = default;

        BaseProgressLoader(const BaseProgressLoader &) = default;

        BaseProgressLoader &operator=(const BaseProgressLoader &) = default;

        explicit BaseProgressLoader(const std::string &root_path);

        progress_t load(size_t player_id) override;

        void save(size_t player_id, progress_t &progress) override;

        bool has_progress(size_t player_id);


    private:
        std::string path;

    };
} // namespace game