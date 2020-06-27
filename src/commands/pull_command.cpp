#include "pull_command.h"

#include <cstdio>
#include <iostream>
#include "hoops_env.h"
#include "util.h"

namespace hoops {

PullCommand::PullCommand(HoopsEnvironment* env)
    : Command(
          "Usage:\n"
          "-pull <player full name>\n"
          "   Returns stats for given player.\n",
          env) {}

PullCommand::~PullCommand() {}

bool PullCommand::IsValidCommand(const std::string& command) {
  return command == "-pull" || command == "-p";
}

// Help command won't take arguments.
bool PullCommand::Process(std::vector<std::string> arguments) {
  if (arguments.size() == 0) {
    std::cout << usage_message();
  } else {
    const std::string& full_name = collapse_vector(arguments);
    auto player = env()->GetPlayer(full_name);
    if (player.id_info.last_name.empty()) {
      // If the name is empty, it's most likely invalid.
      std::cout << "Couldn't find given player.\n";
      return true;
    }
    std::cout << "Getting " << player.GetFullName() << "\n";
    if (!env()->FillAllStats(&player)) {
      // TODO: For now, the scraper won't return errors. Should later write
      // these errors in a log to later examine.
      std::cout << "Error retrieving player.\n";
    } else {
      OutputStatistics(player);
    }
  }
  return true;
}

bool PullCommand::Process() {
  std::cout << usage_message();
  return true;
}

void PullCommand::OutputStatistics(const PlayerMetadata& player) {
  printf(
      "\n-----------------\n%s(%s %s) has played in %lu regular season(s) in "
      "the NBA.\n",
      player.id_info.legal_name.c_str(), player.id_info.first_name.c_str(),
      player.id_info.last_name.c_str(),
      player.career_info.per_game_seasons.size());
  if (player.career_info.per_game_seasons.size() == 0) {
    return;
  }
  auto& latest_season = player.career_info.per_game_seasons.back();
  printf(
      "He averaged %3.2f points per game in the %s season for %s, shooting "
      "%0.3f percent from the field.\n",
      latest_season.points, latest_season.season_info.season.c_str(),
      latest_season.season_info.team.c_str(),
      latest_season.field_goal_percentage);
  printf(
      "He was originally drafted in the %s by the %s,\nafter playing for the "
      "%s.\n",
      player.career_info.draft.c_str(), player.career_info.draft_team.c_str(),
      player.school_info.high_school.c_str());

  if (player.career_info.per_game_seasons.size() < 2) {
    std::cout << "In his one year in the NBA, his accomplishments include ";
    for (const std::string& achievement : player.career_info.achievements) {
      std::cout << achievement << ", ";
    }
    std::cout << ".\n----------\n";
    return;
  }
  if (player.career_info.achievements.size() != 0) {
    std::cout << "His accomplishments include ";
    for (const std::string& achievement : player.career_info.achievements) {
      std::cout << achievement << ", ";
    }
    std::cout << ".\n";
  }

  // Get the lowest and highest scoring seasons.
  auto* best_season = &player.career_info.per_game_seasons.front();
  float best_season_pts = 0;
  auto* worst_season = &player.career_info.per_game_seasons.front();
  float worst_season_pts = 120;  // No one has scored this many points (I think).
  for (auto& season : player.career_info.per_game_seasons) {
    if (season.points > best_season->points) {
      best_season = &season;
    } else if (season.points < worst_season->points) {
      worst_season = &season;
    }
  }

  // Print output for best season stats.
  printf(
      "His best season was in the %s season at age %i, playing %s:\npts: "
      "%3.2f, asts: %3.2f, steals: "
      "%3.2f, blocks: %3.2f\nturnovers: %3.2f, minutes: %3.2f, fgp: %3.2f, "
      "fouls: %3.2f\n",
      best_season->season_info.season.c_str(), best_season->season_info.age,
      best_season->season_info.position.c_str(), best_season->points,
      best_season->assists, best_season->steals, best_season->blocks,
      best_season->turnovers, best_season->minutes_played,
      best_season->field_goal_percentage, best_season->personal_fouls);

  // Print output for worst season stats.
  printf(
      "His worst season was in the %s season at age %i, playing %s:\npts: "
      "%3.2f, asts: %3.2f, steals: "
      "%3.2f, blocks: %3.2f\nturnovers: %3.2f, minutes: %3.2f, fgp: %3.2f, "
      "fouls: %3.2f\n-------------\n",
      worst_season->season_info.season.c_str(), worst_season->season_info.age,
      worst_season->season_info.position.c_str(), worst_season->points,
      worst_season->assists, worst_season->steals, worst_season->blocks,
      worst_season->turnovers, worst_season->minutes_played,
      worst_season->field_goal_percentage, worst_season->personal_fouls);
}

}  // namespace hoops