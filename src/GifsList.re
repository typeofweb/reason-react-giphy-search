open Belt;

let component = ReasonReact.statelessComponent("Gifs List");

let renderGifs = (gifs: Gifs.gifs) =>
  gifs
  |> List.toArray
  |. Array.map((gif: Gifs.singleGif) =>
       <li key=gif.url>
         <video
           width=gif.width
           height=gif.height
           src=gif.mp4
           autoPlay=true
           loop=true
         />
       </li>
     )
  |> ReasonReact.arrayToElement;

let make = (~gifs, _children) => {
  ...component,
  render: _self => <ul> (renderGifs(gifs)) </ul>,
};
