.PHONY: clean All

All:
	@echo "----------Building project:[ Game - Release ]----------"
	@cd "Game" && "$(MAKE)" -f  "Game.mk"
clean:
	@echo "----------Cleaning project:[ Game - Release ]----------"
	@cd "Game" && "$(MAKE)" -f  "Game.mk" clean
