#ifndef PLAYER_METADATA_H_
#define PLAYER_METADATA_H_

#include <array>
#include <list>
#include <string>
#include <utility>
#include <vector>

namespace hoops {

class PlayerMetadata {
 public:
  struct SchoolInformation {
    std::string college;
    std::string college_url;
    std::string high_school;
    std::string high_school_url;
  } school_info;

  static const std::array<std::string, 4> school_tags;

  struct IDInformation {
    std::string first_name;
    std::string last_name;
    std::string url;
    std::string birth_date;
    std::string born;
    std::string born_date_url;
    std::string born_home_url;
    std::string born_year_url;
    std::string legal_name;
    std::string twitter;
    std::string pronunciation;
  } id_info;

  static const std::array<std::string, 10> id_tags;

  struct PhysicalInformation {
    std::string position;
    std::string height;
    int weight;
    std::string shoots;
  } physical_info;

  static const std::array<std::string, 4> physical_tags;

  struct CareerInformation {
    int start_year;
    int end_year;
    std::string draft;
    std::string draft_team_url;
    std::string draft_year_url;
    std::string nba_debut;
    std::string nba_debut_url;
    int recruiting_rank;
    int recruiting_rank_year;
    std::string recruiting_rank_year_url;
    bool in_hall_of_fame;
    std::vector<std::string> achievements;

    // Has relevant information for a season played by a player.
    struct SeasonInformation {
      std::string season;
      int age;
      std::string team;
      std::string league;
      std::string position;
    };

    // Stats for "PerGame" and "Totals" stat line.
    struct PerGameStatLine {
      SeasonInformation season_info;
      int games;
      int games_started;
      float minutes_played;
      float field_goals_made;
      float field_goals_attempt;
      float field_goal_percentage;
      float three_points_made;
      float three_points_attempt;
      float three_points_percentage;
      float two_points_made;
      float two_points_attempt;
      float two_points_percentage;
      float effective_field_goal_percentage;
      float free_throws_made;
      float free_throws_attempt;
      float free_throws_percentage;
      float offensive_rebounds;
      float defensive_rebounds;
      float total_rebounds;
      float assists;
      float steals;
      float blocks;
      float turnovers;
      float personal_fouls;
      float points;
    };

    std::list<PerGameStatLine> per_game_seasons;
    std::list<PerGameStatLine> per_game_playoff_seasons;
    std::list<PerGameStatLine> totals_seasons;
    std::list<PerGameStatLine> totals_playoff_seasons;
    std::list<PerGameStatLine> totals_all_star_seasons;

    // Stats for "Per 36" stat line.
    struct Per36StatLine {
      SeasonInformation season_info;
      int games;
      int games_started;
      float minutes_played;
      float field_goals_made;
      float field_goals_attempt;
      float field_goal_percentage;
      float three_points_made;
      float three_points_attempt;
      float three_points_percentage;
      float two_points_made;
      float two_points_attempt;
      float two_points_percentage;
      float free_throws_made;
      float free_throws_attempt;
      float free_throws_percentage;
      float offensive_rebounds;
      float defensive_rebounds;
      float total_rebounds;
      float assists;
      float steals;
      float blocks;
      float turnovers;
      float personal_fouls;
      float points;
    };

    std::list<Per36StatLine> per_36_seasons;
    std::list<Per36StatLine> per_36_playoff_seasons;

    // Stats for "Per 100 Poss" stat line. (only last two + per36).
    struct Per100StatLine {
      SeasonInformation season_info;
      int games;
      int games_started;
      float minutes_played;
      float field_goals_made;
      float field_goals_attempt;
      float field_goal_percentage;
      float three_points_made;
      float three_points_attempt;
      float three_points_percentage;
      float two_points_made;
      float two_points_attempt;
      float two_points_percentage;
      float free_throws_made;
      float free_throws_attempt;
      float free_throws_percentage;
      float offensive_rebounds;
      float defensive_rebounds;
      float total_rebounds;
      float assists;
      float steals;
      float blocks;
      float turnovers;
      float personal_fouls;
      float points;
      float offensive_rating;
      float defensive_rating;
    };

    std::list<Per100StatLine> per_100_seasons;
    std::list<Per100StatLine> per_100_playoff_seasons;

    // Stats for "Advanced" stat line.
    struct AdvancedStatLine {
      SeasonInformation season_info;
      int games;
      float minutes_played;
      float player_effiency_rating;
      float field_goals_attempt;
      float true_shooting_percentage;
      float three_points_attempt_rate;
      float free_throws_attempt_rate;
      float offensive_rebounds_percentage;
      float defensive_rebounds_percentage;
      float total_rebounds_percentage;
      float assists_percentage;
      float steals_percentage;
      float blocks_percentage;
      float turnovers_percentage;
      float usage_percentage;
      float offensive_win_shares;
      float defensive_win_shares;
      float win_shares;
      float win_shares_per_48;
      float obpm;
      float dbpm;
      float bpm;
      float vorp;
    };

    std::list<AdvancedStatLine> advanced_seasons;
    std::list<AdvancedStatLine> advanced_playoff_seasons;

    // Stats for "Shooting" stat line.
    struct ShootingStatLine {
      SeasonInformation season_info;
      int games;
      float minutes_played;
      float field_goals_percentage;
      float average_distance;
      float two_points_number_percentage;

      // % of FGAs that are x distance from the basket.
      float distance_0_3_percentage;
      float distance_3_10_percentage;
      float distance_10_16_percentage;
      float distance_16_percentage;
      float three_points_number_percentage;
      float two_points_field_percentage;

      // FG% on FGAs that are x feet from the basket.
      float distance_0_3_field_percentage;
      float distance_3_10_field_percentage;
      float distance_10_16_field_percentage;
      float distance_16_field_percentage;
      float three_points_field_percentage;

      float two_points_assisted;
      float dunks_number_percentage;
      float dunks_made;
      float three_points_assisted;
      float corner_three_attempt_percentage;
      float corner_three_field_percentage;
      float heave_attempt;
      float heave_made;
    };

    std::list<ShootingStatLine> shooting_seasons;
    std::list<ShootingStatLine> shooting_playoff_seasons;

    // Stats for "Play by Play" stat line.
    struct PlayStatLine {
      SeasonInformation season_info;
      int games;
      float minutes_played;
      float point_guard_percentage;
      float shooting_guard_percentage;
      float small_forward_percentage;
      float power_forward_percentage;
      float center_percentage;
      float plus_minus_on;
      float plus_minus_net;
      float bad_pass;
      float lost_ball;
      float shooting_fouls;
      float offensive_fouls;
      float shooting_fouls_drawn;
      float offensive_fouls_drawn;
      float assisted_points;
      float and_ones;
      float blocked_attempt;
    };

    std::list<PlayStatLine> play_seasons;
    std::list<PlayStatLine> play_playoff_seasons;

    struct CareerStats {
      int total_games;

      // average <stat> per game for their career.
      float pts;
      float trb;
      float ast;

      // career stat percentage.
      float fgp;
      float fg3p;
      float ftp;
      float efgp;

      // shares.
      float per;
      int ws;
    } career_stats;

    struct TeamInfo {
      // TODO: for now, team_name will have the full parsed name. meaning it'll
      // have the team name and the year. we can parse it to isolate the team
      // name and year onto different member variables. This would require maybe
      // creating new class for this.
      std::string team_name;
      std::string link;
      int number;
    };

    // A player will have played for several teams or a team but with different
    // uniform number.
    std::list<TeamInfo> teams_info;
  } career_info;

  static const std::array<std::string, 11> career_tags;
  void AddAttribute(const std::string& attribute, const std::string& value);
  std::string GetFullUrl() const;
  std::string GetFullName() const;
  static std::string GetFirstName(const std::string& full_name);
  static std::string GetLastName(const std::string& full_name);
  void AddSchoolInformation(const std::string& attribute,
                            const std::string& value);
  void AddIDInformation(const std::string& attribute, const std::string& value);
  void AddPhysicalInformation(const std::string& attribute,
                              const std::string& value);
  void AddCareerInformation(const std::string& attribute,
                            const std::string& value);
  void AddAchievement(const std::string& achievement);
  CareerInformation::CareerStats GetCareerStats();
  void AddCareerStat(const std::string& stat_type, float value);
  void AddTeamInfo(PlayerMetadata::CareerInformation::TeamInfo team_info);
};

}  // namespace hoops

#endif  // PLAYER_METADATA_H_