extends SuperClock


# Called when the node enters the scene tree for the first time.
func _ready():
	parse_all()
	new_day()
