//  _______   __ __   __  _____   __  __  __
// |   __| |_/  |  \_/  |/  _  \ /  \/  \|  |     fkYAML: A C++ header-only YAML library (supporting
// code) |   __|  _  < \_   _/|  ___  |    _   |  |___  version 0.4.2
// |__|  |_| \__|  |_|  |_|   |_|___||___|______| https://github.com/fktn-k/fkYAML
//
// SPDX-FileCopyrightText: 2023-2025 Kensuke Fukutani <fktn.dev@gmail.com>
// SPDX-License-Identifier: MIT

#include <iomanip>
#include <iostream>

#include <fkYAML/node.hpp>

int main() {
    // create a container node.
    fkyaml::node sequence_node = {1, 2, 3};
    // get an iterator to the first sequence element.
    fkyaml::node::iterator it = sequence_node.begin();
    fkyaml::node::const_iterator end_it = sequence_node.cend();

    // print all the elements.
    // note `iterator` and `const_iterator` are comparable.
    for (; it != end_it; ++it) {
        std::cout << *it << std::endl;
    }

    it = sequence_node.begin();
    try {
        // key() cannot be called on an iterator pointing to a sequence element.
        std::cout << it.key() << std::endl;
    } catch (const fkyaml::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
