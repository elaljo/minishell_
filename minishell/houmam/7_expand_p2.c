/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_expand_p2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:31:08 by hait-sal          #+#    #+#             */
/*   Updated: 2023/09/09 16:22:02 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Function to check if a character is alphanumeric or underscore
int is_alnum(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_';
}

// Function to expand a single variable
void expand_variable(const char* var_name, char* expanded, size_t* j) {
    // Lookup the variable in the system's environment
    const char* value;
    value = getenv(var_name);

    // If the variable exists, append its value to the expanded string
    if (value != NULL)
    {
        strcpy(expanded + *j, value);
        *j += strlen(value);
    }
}

// expand variables in a string, handling variables and escaped quotes
char* expand_variables(char* input) {
    size_t input_length = strlen(input);
    char* expanded = (char*)malloc((input_length * 2 + 1) * sizeof(char));

    if (expanded == NULL) {
        return NULL; // Allocation failed
    }

    size_t i = 0, j = 0;
    int inside_double_quotes = 0;
    int inside_single_quotes = 0;

    while (input[i]) {
        if (input[i] == '\\') {
            i++; // Skip the escape character
            if (input[i] == '"' || input[i] == '\'') {
                // Remove the escape character before a double quote or single quote
                expanded[j++] = input[i++];
            }
        } else if (input[i] == '\'') {
            inside_double_quotes = !inside_double_quotes;
            expanded[j++] = input[i++];
        } else if (input[i] == '"') {
            inside_single_quotes = !inside_single_quotes;
            expanded[j++] = input[i++];
        } else if (!inside_double_quotes && input[i] == '$') {
            i++; // Skip '$'

            // Check for consecutive '$$' and skip them
            if (input[i] == '$') {
                i++; // Skip the second '$'
                continue; // Skip expanding and continue the loop
            }

            char var_name[256];
            size_t k = 0;

            // Read the variable name until a non-alphanumeric character or end of string
            while (is_alnum(input[i]) || input[i] == '_') {
                var_name[k++] = input[i++];
            }

            var_name[k] = '\0';

            // Expand the variable
            expand_variable(var_name, expanded, &j);
        } else {
            expanded[j++] = input[i++];
        }
    }

    expanded[j] = '\0';
	// printf("expand-------------> %s\n", expanded);
    return expanded;
}