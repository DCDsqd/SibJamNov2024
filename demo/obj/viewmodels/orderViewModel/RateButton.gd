extends Button

@export var value : int = 0
@export var viewModel : OrderHud

func _ready():
	connect("button_up", press)

func press():
	if(!viewModel):
		print("Button: viewModel is null")
		return
	
	viewModel.rate_current_order(value)
