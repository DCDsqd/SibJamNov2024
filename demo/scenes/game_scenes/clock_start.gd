extends SuperClock


# Called when the node enters the scene tree for the first time.
func _ready():
	parse_all()
	update_day_pulls()
	update_custommer()
	update_quests()
