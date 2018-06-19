open Belt;

[@bs.val] [@bs.scope "console"] external consoleError : 'a => unit = "error";

type action =
  | FetchingStarted(string)
  | DataFetched(Gifs.gifsResponse)
  | FetchError;

type state = {
  text: string,
  isFetching: bool,
  response: Gifs.gifsResponse,
};

let initialState = () => {text: "", isFetching: false, response: None};

let _fetchGifsInternal = (text, {ReasonReact.send}) => {
  Js.Promise.(
    GiphyApi.searchGifs(text)
    |> then_(response => send(DataFetched(response)) |> resolve)
    |> catch(err => {
         consoleError(err);
         resolve(send(FetchError));
       })
  )
  |> ignore;
  ();
};

let fetchGifs = Utils.debounce2(_fetchGifsInternal, 300);

let reducer = (action: action, state: state) =>
  switch (action) {
  | FetchingStarted("") =>
    ReasonReact.Update({...state, isFetching: false, response: Some([])})
  | FetchingStarted(text) =>
    ReasonReact.UpdateWithSideEffects(
      {...state, isFetching: true},
      fetchGifs(text),
    )
  | DataFetched(gifs) =>
    ReasonReact.Update({...state, response: gifs, isFetching: false})
  | FetchError => ReasonReact.NoUpdate
  };

let component = ReasonReact.reducerComponent("GiphsListContainer");

let make = (~text: string, _children) => {
  ...component,
  reducer,
  initialState,
  willReceiveProps: self => {...self.state, text},
  didMount: ({ReasonReact.send}) => {
    Js.log(text);
    send(FetchingStarted(text));
  },
  didUpdate: ({oldSelf, newSelf}) => {
    if (oldSelf.state.text !== newSelf.state.text) {
      newSelf.send(FetchingStarted(text));
    };
    ();
  },
  render: self =>
    switch (self.state.response, self.state.isFetching) {
    | (Some(gifs), false) => <GifsList gifs />
    | _ =>
      <div className="loading-indicator">
        ({j|Ładowanie…|j} |> ReasonReact.string)
      </div>
    },
};
