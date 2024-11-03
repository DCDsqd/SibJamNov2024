extends Button

@export var viewModel : OrderHud

func _ready():
	connect("button_up", press)

func press():
	if(!viewModel):
		print("Button: viewModel is null")
		return
	
	viewModel.unrate_current_order()
