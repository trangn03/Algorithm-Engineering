///////////////////////////////////////////////////////////////////////////////
// disks.hpp
// 
// Definitions for two algorithms that each solve the alternating disks
// problem.
//
// As provided, this header has four functions marked with TODO comments.
// You need to write in your own implementation of these functions.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

// TODO
#include <functional>
#include <iostream>

enum disk_color { DISK_DARK, DISK_LIGHT};

class disk_state {
private:
  std::vector<disk_color> _colors;

public:
  disk_state(size_t light_count)
    : _colors(light_count * 2, DISK_DARK) {

    assert(light_count > 0);

    for (size_t i = 0; i < _colors.size(); i += 2) {
      _colors[i] = DISK_LIGHT;
    }
  }

  bool operator== (const disk_state& rhs) const {
    return std::equal(_colors.begin(), _colors.end(), rhs._colors.begin());
  }

  size_t total_count() const {
    return _colors.size();
  }

  size_t light_count() const {
    return total_count() / 2;
  }

  size_t dark_count() const {
    return light_count();
  }

  bool is_index(size_t i) const {
    return (i < total_count());
  }

  disk_color get(size_t index) const {
    assert(is_index(index));
    return _colors[index];
  }

  void swap(size_t left_index) {
    assert(is_index(left_index));
    auto right_index = left_index + 1;
    assert(is_index(right_index));
    std::swap(_colors[left_index], _colors[right_index]);
  }

  std::string to_string() const {
    std::stringstream ss;
    bool first = true;
    for (auto color : _colors) {
      if (!first) {
        ss << " ";
      }

      if (color == DISK_LIGHT) {
        ss << "L";
      } else {
        ss << "D";
      }

      first = false;
    }
    return ss.str();
  }

  // Return true when this disk_state is in alternating format. That means
  // that the first disk at index 0 is light, the second disk at index 1
  // is dark, and so on for the entire row of disks.
  bool is_initialized() const {
    for (size_t i = 0; i < total_count(); i++) {
      if (i % 2 == 0){
          // even = dark
          // Check if the color at even position is not at light state
          // then return false
          if(get(i) == DISK_DARK) {
            return false;
          } 
      } else {
          // odd = light
          // Check if the color at odd position is not at dark state
          // then return false
          if (get(i) == DISK_LIGHT) {
            return false;
          }
        }
    }
    return true;
  }

  // Return true when this disk_state is fully sorted, with all dark disks
  // on the left (low indices) and all light disks on the right (high
  // indices).
  bool is_sorted() const {
    for (size_t i = 0; i < total_count(); i++) {
      if (i < total_count() / 2) {
        if (get(i) != DISK_DARK) {
          return false;
        } 
      } else {
        if (get(i) != DISK_LIGHT) {
          return false;
        }
      }
    }
    return true;
  }
};

// Data structure for the output of the alternating disks problem. That
// includes both the final disk_state, as well as a count of the number
// of swaps performed.
class sorted_disks {
private:
  disk_state _after;
  unsigned _swap_count;
  
public:
  
  sorted_disks(const disk_state& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }
  
  sorted_disks(disk_state&& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }
  
  const disk_state& after() const {
    return _after;
  }
  
  unsigned swap_count() const {
    return _swap_count;
  }
};

// Algorithm that sorts disks using the alternate algorithm.
sorted_disks sort_alternate(const disk_state& before) {
  disk_state current_state = before;
  unsigned swap_count = 0;
  for (size_t i = 0; i <= current_state.light_count(); i++) {
    if (i % 2 == 0) {
      for (size_t a = 0; a <= (2*current_state.light_count()) - 1; a += 2) {
        if (current_state.get(a) == DISK_LIGHT && current_state.get(a + 1) == DISK_DARK) {
          current_state.swap(a);
          swap_count++;
        }
      }
    } else {
      for (size_t b = 1; b <= (2*current_state.light_count())-2; b += 2) {
        if (current_state.get(b) == DISK_LIGHT && current_state.get(b+1) == DISK_DARK) {
          current_state.swap(b);
          swap_count++;
        }
      }
    }
  }
  return sorted_disks(current_state, swap_count);
}

// Algorithm that sorts disks using the lawnmower algorithm.
sorted_disks sort_lawnmower(const disk_state& before) {
  disk_state current_state = before;
  unsigned swap_count = 0;
  for (size_t i = 0; i <= (current_state.light_count() + 1) / 2; i++) {
    for (size_t a = 0; a <= (2*current_state.light_count()) - 2; a++) {
      if (current_state.get(a) == DISK_LIGHT && current_state.get(a+1) == DISK_DARK) {
        current_state.swap(a);
        swap_count++;
      }
    }
    for (size_t b = (2*current_state.light_count()) - 1; b >= 1; b--) {
      if (current_state.get(b) == DISK_DARK && current_state.get(b-1) == DISK_LIGHT) {
        current_state.swap(b-1);
        swap_count++;
      }
    }
  }
  return sorted_disks(current_state, swap_count);
}
  
