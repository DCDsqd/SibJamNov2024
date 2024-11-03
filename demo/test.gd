extends Node3D

func _ready():
	var angel : ArcAngel = ArcAngel.new()
	#God.set_debug_output(true)
	#angel.set_debug_output(true)
	angel.set_file("res://untitled-project-2024-11-01-233012.json")
	angel.activate()
