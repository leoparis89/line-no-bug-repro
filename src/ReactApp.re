module App = {
  let style =
    ReactDOM.Style.make(~fontSize="1.5em", ~display="flex", ~gap="0.5em", ());

  [@react.component]
  let make = () =>
    <div>
      <h1> {React.string("melange-opam-template")} </h1>
      {["Hello " ++ World.name ++ "!", "This is ReasonReact!"]
       |> List.map(text =>
            <div key=text style>
              {React.string(text)}
              <button
                onClick={_ => text |> Speech.makeUtterance |> Speech.speak}>
                {React.string("speak")}
              </button>
            </div>
          )
       |> Array.of_list
       |> React.array}
    </div>;
};

let () =
  switch (ReactDOM.querySelector("#root")) {
  | None =>
    Js.Console.error("Failed to start React: couldn't find the #root element")
  | Some(element) =>
    let root = ReactDOM.Client.createRoot(element);
    ReactDOM.Client.render(root, <App />);
  };

module OtherModule = {
  type t = {
    name: string,
    age: int,
  };
};

type typeInCurrentModule = {
  name: string,
  age: int,
};

// Following error is reported at line 1
//
// File "src/ReactApp.re", line 1:
// Error (warning 9 [missing-record-field-pattern]): the following labels are not bound in this record pattern:
// age
let bugRepro = (arg: OtherModule.t) => {
  let OtherModule.{name} = arg;
  let _ = name;
  ();
}

// Line no bug doesn't happen if type is defined in current module
let noBugRepro = (arg: typeInCurrentModule) => {
  let {name} = arg;
  let _ = name;
  ();
}
