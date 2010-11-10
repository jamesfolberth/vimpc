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

   playlist.hpp - handling of the mpd playlist interface 
   */

#ifndef __UI__PLAYLIST
#define __UI__PLAYLIST

#include "song.hpp"
#include "window.hpp"

namespace Mpc
{
   class Client;
}

namespace Ui
{
   class PlaylistWindow : public Ui::Window
   {
   public:
      PlaylistWindow(Ui::Screen const & screen, Mpc::Client& client);
      ~PlaylistWindow();

   public:
      void AddSong(Mpc::Song * newSong);
      Mpc::Song const * const GetSong(uint32_t songIndex);

   public:
      void Print(uint32_t line) const;
      void Confirm() const;
      void Scroll(int32_t scrollCount);
      void ScrollTo(uint16_t scrollLine);
      void Search(std::string const & searchString) const;

   private:
      size_t BufferSize() const { return buffer_.size(); }

   private:
      int64_t LimitCurrentSelection(int64_t currentSelection) const;

   private:
      int64_t currentSelection_;

      Mpc::Client & client_;

      typedef std::vector<Mpc::Song *> SongBuffer;
      SongBuffer buffer_;
   };
}

#endif