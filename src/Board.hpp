#pragma once

#include <ostream>
#include <vector>

struct Ship {
    size_t length;
    std::string type;

    Ship(size_t length, std::string type) : length(length), type(type) {}
};

enum class Field {
    SHIP,
    WATER,
    HIT
};

class ITargetBoard {
  public:
    virtual bool fire(char col, unsigned char row) = 0;
    virtual bool fleet_destroyed() const = 0;
    virtual size_t dim() const = 0;

    virtual ~ITargetBoard() {}
};

class Board : public ITargetBoard {
  private:


    bool is_valid_position(char col, unsigned char row) const;
    void place_ship(char col, unsigned char row, size_t length, int orientation);
    bool can_place_ship(char col, unsigned char row, size_t length, int orientation) const;

public:
    Board(size_t dim);
    size_t board_dim;
    std::vector<std::vector<Field>> grid;
    void place_fleet_randomly(const std::vector<Ship>& fleet);
    void place_fleet_manually(const std::vector<Ship>& fleet);

    virtual bool fire(char col, unsigned char row) override;
    virtual bool fleet_destroyed() const override;
    virtual size_t dim() const override;

    Field at(char col, unsigned char row) const;

    void set_ship_manually(char col, unsigned char row);
};

std::ostream& operator<<(std::ostream& os, const Board& board);
