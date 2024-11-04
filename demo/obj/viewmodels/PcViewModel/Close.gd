extends Button

@export var viewModel : PcViewModel

func _ready():
	connect("button_up", press)

func press():
	if(!viewModel):
		print("Button: viewModel is null")
		return
	
	viewModel.close_window()
