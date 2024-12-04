#include <iostream>
#include <vector>
#include <string>
#include <limits>

// Structure Recipe
struct Recipe {
    int id;
    std::string name;
    std::vector<std::string> ingredients;
    std::string instructions;
};

void displayMenu();
void addRecipe(std::vector<Recipe> &recipes, int &next_id);
void viewAllRecipes(const std::vector<Recipe> &recipes);
void viewRecipeById(const std::vector<Recipe> &recipes);
void updateRecipe(std::vector<Recipe> &recipes);
void deleteRecipe(std::vector<Recipe> &recipes);

int getIntegerInput(const std::string &prompt);
std::string getLineInput(const std::string &prompt);
std::vector<std::string> getIngredientsInput();

int main() {
    std::vector<Recipe> recipes;
    int next_id = 1;
    bool running = true;

    while (running) {
        displayMenu();
        int choice = getIntegerInput("Select an option (1-6): ");

        switch (choice) {
            case 1:
                addRecipe(recipes, next_id);
                break;
            case 2:
                viewAllRecipes(recipes);
                break;
            case 3:
                viewRecipeById(recipes);
                break;
            case 4:
                updateRecipe(recipes);
                break;
            case 5:
                deleteRecipe(recipes);
                break;
            case 6:
                std::cout << "Exiting Recipe Management System. Goodbye!\n";
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Please select a valid option.\n";
        }
    }

    return 0;
}

// Function to display the main menu
void displayMenu() {
    std::cout << "\n=== Recipe Management System ===\n";
    std::cout << "1. Add a New Recipe\n";
    std::cout << "2. View All Recipes\n";
    std::cout << "3. View a Recipe by ID\n";
    std::cout << "4. Update a Recipe\n";
    std::cout << "5. Delete a Recipe\n";
    std::cout << "6. Exit\n";
}

// Function to add a new recipe
void addRecipe(std::vector<Recipe> &recipes, int &next_id) {
    Recipe new_recipe;
    new_recipe.id = next_id;
    new_recipe.name = getLineInput("Enter the recipe name: ");

    if (new_recipe.name.empty()) {
        std::cout << "Recipe name cannot be empty.\n";
        return;
    }

    std::cout << "Enter ingredients one by one. Type 'done' when finished:\n";
    new_recipe.ingredients = getIngredientsInput();

    new_recipe.instructions = getLineInput("Enter the preparation instructions: ");
    if (new_recipe.instructions.empty()) {
        std::cout << "Instructions cannot be empty.\n";
        return;
    }

    recipes.push_back(new_recipe);
    std::cout << "Recipe '" << new_recipe.name << "' added with ID " << new_recipe.id << ".\n";
    next_id++;
}

// Function to view all recipes
void viewAllRecipes(const std::vector<Recipe> &recipes) {
    if (recipes.empty()) {
        std::cout << "No recipes available.\n";
        return;
    }

    std::cout << "\n--- All Recipes ---\n";
    for (const auto &recipe : recipes) {
        std::cout << "ID: " << recipe.id << " | Name: " << recipe.name << "\n";
    }
}

// Function to view a recipe by ID
void viewRecipeById(const std::vector<Recipe> &recipes) {
    if (recipes.empty()) {
        std::cout << "No recipes available.\n";
        return;
    }

    int id = getIntegerInput("Enter the Recipe ID: ");
    bool found = false;

    for (const auto &recipe : recipes) {
        if (recipe.id == id) {
            std::cout << "\n--- Recipe ID: " << recipe.id << " ---\n";
            std::cout << "Name: " << recipe.name << "\n";
            std::cout << "Ingredients:\n";
            for (size_t i = 0; i < recipe.ingredients.size(); ++i) {
                std::cout << "  " << (i + 1) << ". " << recipe.ingredients[i] << "\n";
            }
            std::cout << "Instructions:\n" << recipe.instructions << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "No recipe found with ID " << id << ".\n";
    }
}

// UpdateRecipe
void updateRecipe(std::vector<Recipe> &recipes) {
    if (recipes.empty()) {
        std::cout << "No recipes available to update.\n";
        return;
    }

    int id = getIntegerInput("Enter the Recipe ID to update: ");
    bool found = false;

    for (auto &recipe : recipes) {
        if (recipe.id == id) {
            std::cout << "\nUpdating Recipe ID: " << id << " - " << recipe.name << "\n";
            std::string new_name = getLineInput("Enter new name (press Enter to keep '" + recipe.name + "'): ");
            if (!new_name.empty()) {
                recipe.name = new_name;
            }

            std::cout << "Update ingredients? (yes/no): ";
            std::string choice;
            std::getline(std::cin, choice);
            if (choice == "yes" || choice == "Yes" || choice == "y" || choice == "Y") {
                std::cout << "Enter new ingredients one by one. Type 'done' when finished:\n";
                recipe.ingredients = getIngredientsInput();
            }

            std::string new_instructions = getLineInput("Enter new instructions (press Enter to keep current instructions): ");
            if (!new_instructions.empty()) {
                recipe.instructions = new_instructions;
            }

            std::cout << "Recipe ID " << id << " has been updated.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "No recipe found with ID " << id << ".\n";
    }
}

// DeleteRecipe
void deleteRecipe(std::vector<Recipe> &recipes) {
    if (recipes.empty()) {
        std::cout << "No recipes available to delete.\n";
        return;
    }

    int id = getIntegerInput("Enter the Recipe ID to delete: ");
    bool found = false;

    for (size_t i = 0; i < recipes.size(); ++i) {
        if (recipes[i].id == id) {
            std::cout << "Are you sure you want to delete '" << recipes[i].name << "'? (yes/no): ";
            std::string confirm;
            std::getline(std::cin, confirm);
            if (confirm == "yes" || confirm == "Yes" || confirm == "y" || confirm == "Y") {
                recipes.erase(recipes.begin() + i);
                std::cout << "Recipe ID " << id << " has been deleted.\n";
            } else {
                std::cout << "Deletion cancelled.\n";
            }
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "No recipe found with ID " << id << ".\n";
    }
}

int getIntegerInput(const std::string &prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            return value;
        } else {
            std::cout << "Invalid input. Please enter a numeric value.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }
    }
}

std::string getLineInput(const std::string &prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

std::vector<std::string> getIngredientsInput() {
    std::vector<std::string> ingredients;
    while (true) {
        std::string ingredient = getLineInput("Ingredient: ");
        if (ingredient == "done" || ingredient == "DONE" || ingredient == "Done") {
            break;
        } else if (!ingredient.empty()) {
            ingredients.push_back(ingredient);
        }
    }
    return ingredients;
}
