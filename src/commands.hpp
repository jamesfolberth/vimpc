/*
   Vimpc
   Copyright (C) 2010 Nathan Sweetman

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   commands.hpp - ex mode input handling 
   */

#ifndef __UI__COMMANDS
#define __UI__COMMANDS

#include <string>
#include <map>
#include <vector>

#include "handler.hpp"
#include "inputmode.hpp"
#include "modewindow.hpp"
#include "player.hpp"

namespace Main
{
   class Settings;
   class Vimpc;
}

namespace Ui
{
   class Screen;

   // Handles all input received whilst in command mode
   class Commands : public InputMode, public Player
   {

   public:
      Commands(Ui::Screen & screen, Mpc::Client & client, Main::Settings & settings);
      ~Commands();

   public: // Ui::Handler Inherits
      void InitialiseMode();
      bool Handle(int input);

   private:
      //
      void GenerateInputString(int const input);

      bool InputModeHandler(std::string input);

   public:
      // Checks if there is any aliases defined for a command, recursively calling
      // until a proper command is found then executes that command
      //
      // \param[in] input The command string to execute, including the arguments
      bool ExecuteCommand(std::string const & input);


      // Executes \p command using \p arguments
      //
      // \param[in] command   The command to execute
      // \param[in] arguments The arguments to pass to the command
      bool ExecuteCommand(std::string const & command, std::string const & arguments);

      // Splits the input into command and argument parts
      //
      // \param[in]  input     The string to split
      // \param[out] command   The command part of the string
      // \param[out] arguments The arguments from the string
      void SplitCommand(std::string const & input, std::string & command, std::string & arguments);

      // Handle the settings
      bool Set(std::string const & arguments);

      // Call the cli mpc client
      bool Mpc(std::string const & arguments);

      // Alias a command to a given string
      bool Alias(std::string const & arguments);

      //
      void ResetTabCompletion(int input);

      // Complete the current command, by searching through the command table
      // for commands that begin with the currently set command
      std::string TabComplete(std::string const & command);

   public:
      typedef bool (Ui::Commands::*ptrToMember)(std::string const &);

   private: 
      Main::Settings & settings_;
      Ui::Screen     & screen_;
      bool             initTabCompletion_;

      //Tables
      typedef std::map<std::string, std::string> AliasTable;
      typedef std::map<std::string, ptrToMember> CommandTable;

      AliasTable     aliasTable_;
      CommandTable   commandTable_;

      // Command completion classes
      class TabCompletionMatch 
      {
      public:
         TabCompletionMatch(std::string const & key) : 
            key_(key) 
         {}

      public:
         bool operator() (std::pair<std::string const &, Ui::Commands::ptrToMember> element) 
         {
            std::string input(element.first);
            return (key_.compare(input.substr(0, key_.length())) == 0);
         }

      private:
         std::string key_;
      };
   };
}

#endif