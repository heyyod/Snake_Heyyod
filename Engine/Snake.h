#pragma once

#include "Graphics.h"
#include "Location.h"
#include "Board.h"

class Snake {

private:
	class Segment {
	public:
		void InitHead( const Location& in_loc );
		void InitBody();
		void Follow(const Segment& next);
		void Draw(Board& brd, Color in_c) const;
		void MoveBy(const Location& delta_loc);
		const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};

public:
	Snake(const Location& loc);
	void Reset(const Location& loc);
	void MoveBy( const Location& delta_loc );
	void Grow();
	void Draw( Board& brd );
	Location GetNextHeadLocation(const Location& delta_loc) const;
	bool HeadIsInsiteTile(const Location& headLoc) const;
	bool IsInTile(const Location& goalLoc) const;
	bool IsMaxSize() const;
	Color GetBodyColor() const;
	void DecreaseSize();
	int GetCurrentSize() const;

private:
	bool finishedChangingColor = false;
	static constexpr Color headColor = Colors::Green;
	static constexpr Color bodyColor = Color( 50, 50, 0 );
	static constexpr int nSegmentsMax = 30;
	Segment segments[nSegmentsMax];
	Location deltaloc[nSegmentsMax];
	int nSegments = 1;
};