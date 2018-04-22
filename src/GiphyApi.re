open Belt;

let decodeGifs = json : Gifs.gifsResponse => {
  let data =
    Json.Decode.(
      json
      |> field("data", data =>
           data
           |> array(gif =>
                gif
                |> at(["images", "fixed_height_small"], f =>
                     (
                       {
                         url: f |> field("url", string),
                         mp4: f |> field("mp4", string),
                         height: f |> field("height", string),
                         width: f |> field("width", string),
                       }: Gifs.singleGif
                     )
                   )
              )
         )
    );
  Some(List.fromArray(data));
};

let searchGifs = (text: string) =>
  Js.Promise.(
    Fetch.fetch(
      "https://api.giphy.com/v1/gifs/search?api_key=JL2ng3jv0WFkG1wVXDm71rtuzlx4sHi6&limit=25&offset=0&rating=G&lang=en&q="
      ++ text,
    )
    |> then_(Fetch.Response.json)
    |> then_(json => json |> decodeGifs |> resolve)
  );
