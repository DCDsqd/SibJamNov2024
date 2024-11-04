extends Button

@export var viewModel : OrderHud
@export var to : int

func _ready():
	connect("button_up", press)

func press():
	if(!viewModel):
		print("Button: viewModel is null")
		return
	
	viewModel.swap_sorted(to)
