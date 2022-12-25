#pragma once
#include "common.h"
#include "stream.h"
#include <sstream>
#include <unordered_map>
#include <utility>


namespace unv {

auto static read_first_scalar(const std::string& line) -> std::size_t;
auto static read_n_scalars(const std::string& line, std::size_t n) -> std::vector<std::size_t>;

class Reader {
public:
    Reader() = delete;
    Reader(FileStream& stream) : stream(stream) {};
    ~Reader() { stream.~FileStream(); }

    void read_tags();
    void read_units();
    void read_vertices();
    void read_elements();
    void read_groups();
    void read_dofs();

    auto units() -> UnitsSystem&;
    auto vertices() -> std::vector<Vertex>&;
    auto elements() -> std::vector<Element>&;
    auto groups() -> std::vector<Group>&;

private:
    inline void skip_tag() {
        while (stream.read_line(temp_line) && !is_separator(temp_line)) {
        }
    }

    template <typename T = std::pair<std::vector<std::size_t>, GroupType>>
    auto read_group_elements(std::size_t n_elements) -> T;

    template <typename T = std::pair<std::vector<std::size_t>, GroupType>>
    auto read_group_elements_two_columns(std::size_t n_elements) -> T;

    template <typename T = std::pair<std::vector<std::size_t>, GroupType>>
    auto read_group_elements_single_column() -> T;

    FileStream& stream;
    std::string temp_line;

    UnitsSystem units_system;
    std::vector<Vertex> _vertices;
    std::vector<Element> _elements;
    std::vector<Group> _groups;

    std::unordered_map<std::size_t, std::size_t> vertex_id_map;
    std::unordered_map<std::size_t, std::size_t> element_id_map;
};
} // namespace unv
