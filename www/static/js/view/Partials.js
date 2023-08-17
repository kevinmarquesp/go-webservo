export default class Partials {
    static buildSceneItem(Scene, id) {
        return `<li data-js-scene-item data-js-scene-speed="${Scene.data.speed}" data-js-scene-position="${Scene.data.position.join(",")}" data-js-scene-id="${id}" class="list-group-item d-flex justify-content-between p-2">
            <span style="font-family: monospace" class="text-bold text-center p-2">
                <strong>
                    ${Scene.data.speed}/${Scene.data.position.join(",")}
                </strong>
            </span>
            <div class="btn-group">
                <button type="button" class="btn btn-sm btn-primary dropdown-toggle" data-bs-toggle="dropdown" aria-expanded="false">
                    Opções
                </button>
                <ul class="dropdown-menu">
                    <li>
                        <button type="button" class="dropdown-item">
                            Testar
                        </button>
                    </li>
                    <li>
                        <button data-js-scene-delete-button type="button" class="dropdown-item">
                            Remover
                        </button>
                    </li>
                    <li>
                        <hr class="dropdown-divider"></li>
                    <li>
                        <button type="button" class="dropdown-item">
                            Atualizar
                        </button>
                    </li>
                </ul>
            </div>
        </li>`
    }
}
