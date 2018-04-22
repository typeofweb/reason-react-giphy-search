open Belt;

type action =
  | SearchTextChange(string);

type state = {currentText: string};

let initialState = () => {currentText: ""};

let onInputChange = ({ReasonReact.send}, e) =>
  send(
    SearchTextChange(
      ReactDOMRe.domElementToObj(ReactEventRe.Form.target(e))##value,
    ),
  );

let reducer = (action: action, _state: state) =>
  switch (action) {
  | SearchTextChange(text) => ReasonReact.Update({currentText: text})
  };

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  reducer,
  initialState,
  render: self =>
    <div>
      <input
        placeholder={j|Search gifs…|j}
        value=self.state.currentText
        onChange=(onInputChange(self))
        autoFocus=true
      />
      <GiphsListContainer text=self.state.currentText />
    </div>,
};
