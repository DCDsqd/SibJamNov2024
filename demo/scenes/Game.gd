extends SimpleGameController


func _ready():
	var angel : ArcAngel = ArcAngel.new()
	#God.set_debug_output(true)
	#angel.set_debug_output(true)
	angel.set_file("res://story/project_settings.json")
	angel.activate()
	
	put_int("game_time", 0)
	put_int("game_day", 0)
	
	swap_scene("res://scenes/game_scenes/Scene.tscn")
	
	

