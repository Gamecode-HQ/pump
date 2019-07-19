defmodule Pump.Metrics.GPU do
  require Logger

  def metrics do
    {return, status} = System.cmd(port_path(), [])
    if status == 0 do
      return
      |> String.split("\n")
      |> Enum.reduce([], fn (data, acc) ->
        case String.split(data, ": ", trim: true) do
          [key, value] -> acc ++ [{String.downcase(key), [], String.to_integer(value)}]
          _ -> acc
        end
      end)
    else
        []
    end
  end

  def port_path do
    :pump
    |> Application.app_dir("priv/gpu")
  end
end
